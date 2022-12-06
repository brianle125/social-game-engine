#include <iostream>
#include <stdexcept>
#include <string_view>
#include <sstream>
#include <GameModel.h>
#include <ContentVariant.h>
#include "VariantParser.h"
#include "IRule.h"

using LookupKey = std::string;

GameModel::GameModel() {
	parser = VariantParser();
}

void GameModel::addSetupVariable(LookupKey key, dataVariant value) {
	setup.emplace(key, value);
}

void GameModel::addConstant(LookupKey key, dataVariant value) {
	constants.emplace(key, value);
}

void GameModel::addVariable(LookupKey key, dataVariant value) {
	variables.emplace(key, value);
}

dataVariant GameModel::getVariable(LookupKey key) {
	auto accessors = parser.splitVariableReference(key);
	dataVariant currentVariable;

	//Todo: use Variant Parser to deal with more complex keys like coin.elements.name
	//These elements are now parsed out, next up is to resolve them
	std::vector<string_view>::iterator accessorIndex = accessors.begin();

	while(accessorIndex != accessors.end()) {
		currentVariable = resolveKey(currentVariable, accessors, accessorIndex);
	}	

	return currentVariable;

	//TODO: this may need to be replaced with implicit creation
	throw std::invalid_argument("Variable " + key + " Not Found");
}

dataVariant GameModel::resolveKey(dataVariant currentVariable, std::vector<string_view> accessors, std::vector<string_view>::iterator& index) {
	string_view currentAccessor = *index;

	if(currentAccessor == "elements") {
		if(index + 1 == accessors.end()) 
			throw std::invalid_argument("elements is not valid as the final accessor in a chain");
		dataVariant key(LookupKey{*(index + 1)});
		index += 2; //burns this and the following accessor
		return rva::visit(searchVisitor{}, currentVariable, key);;
	}

	if (currentAccessor == "size") { 
		index += 1;
		return rva::visit(sizeVisitor{}, currentVariable);
	}

	if (currentAccessor == "contains") {
		
	}

	//Default case, where no special commands were invoked, just finds the variable in the lists.
	currentVariable = lookupVariable(LookupKey{currentAccessor});
	index += 1;
	return currentVariable;
}

dataVariant GameModel::lookupVariable(LookupKey key) {
	dataVariant varToReturn;
	auto variableIterator = variables.find(key);
	if(variableIterator != variables.end()) {
		varToReturn = variableIterator->second;
	}
	variableIterator = constants.find(key);
	if(variableIterator != constants.end()) {
		varToReturn = variableIterator->second;
	}
	return varToReturn;
}

std::string GameModel::fillInVariables(std::string_view toParse) {
	auto keys = parser.getKeysFromString(toParse);
	std::vector<std::string> variables;

	for(auto key : keys) {
		// LookupKey lookup;
		dataVariant variable = getVariable(LookupKey{key});
		variables.push_back(rva::visit(toStringVisitor{}, variable));
	}

	return parser.replaceKeysInString(toParse, variables);
}

void GameModel::setVariable(LookupKey key, dataVariant value) {
	auto varToUpdate = variables.find(key);
	if(varToUpdate != variables.end()) {
		varToUpdate->second = value;
		return;
	}

	//TODO: this may need to be replaced with implicit creation
	throw std::invalid_argument("Variable " + key + " Not Found");
}

//These functions are nearly identical and thus repeat code, however
//they express different concepts (creating constant values vs creating variables)
//and separating them avoids confusion.
void GameModel::addSetupVariablesFromJson(json setup) {
	for(auto variable : setup.items()) {
		string keyname = variable.key();
		dataVariant variant = parser.makeVariantFromJson(setup.at(keyname));

		addSetupVariable(keyname, variant);

		cout << keyname << " - " << rva::visit (toStringVisitor{}, variant) << "\n";
	}
}

void GameModel::addConstantsFromJson(json constants) {
	for(auto constant : constants.items()) {
		string keyname = constant.key();
		dataVariant variant = parser.makeVariantFromJson(constants.at(keyname));

		addConstant(keyname, variant);

		cout << keyname << " - " << rva::visit (toStringVisitor{}, variant) << "\n";
	}
}

void GameModel::addVariablesFromJson(json variables) {
	for(auto variable : variables.items()) {
		string keyname = variable.key();
		dataVariant variant = parser.makeVariantFromJson(variables.at(keyname));

		addVariable(keyname, variant);
		cout << keyname << " - " << rva::visit (toStringVisitor{}, variant) << "\n";
	}
}