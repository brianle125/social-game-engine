#include <iostream>
#include <stdexcept>
#include <string_view>
#include <sstream>
#include <GameModel.h>
#include <ContentVariant.h>
#include "VariantParser.h"
#include "IRule.h"

using namespace std;
using LookupKey = string;

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
	auto variableAccess = parser.splitVariableReference(key);
	dataVariant varToReturn;

	//Todo: use Variant Parser to deal with more complex keys like deck.elements.name
	//These elements are now parsed out, next up is to resolve them
	for(auto accessor : variableAccess) {
		auto variableIterator = variables.find(LookupKey{accessor});
		if(variableIterator != variables.end()) {
			varToReturn = variableIterator->second;
		}
		variableIterator = constants.find(LookupKey{accessor});
		if(variableIterator != constants.end()) {
			varToReturn = variableIterator->second;
		}
	}	

	return varToReturn;

	//TODO: this may need to be replaced with implicit creation
	throw std::invalid_argument("Variable " + key + " Not Found");
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