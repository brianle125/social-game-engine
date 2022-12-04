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
	//Todo: use Variant Parser to deal with more complex keys like deck.elements.name
	

	auto varToReturn = variables.find(key);
	if(varToReturn != variables.end()) {
		return varToReturn->second;
	}
	varToReturn = constants.find(key);
	if(varToReturn != constants.end()) {
		return varToReturn->second;
	}

	//TODO: this may need to be replaced with implicit creation
	throw std::invalid_argument("Variable " + key + " Not Found");
}

std::string GameModel::fillInVariables(std::string_view toParse) {
	auto keys = parser.getKeysFromString(toParse);
	std::vector<std::string> variables;

	for(auto key : keys) {
		LookupKey lookup{key};
		dataVariant variable = getVariable(lookup);
		variables.push_back(rva::visit(toStringVisitor{}, variable));
	}

	std::ostringstream parsedString;
	bool writing = true;
	size_t variableIndex = 0;

	for(char c : toParse) {
		if(c == '{') {
			writing = false;
		}
		if(writing) {
			parsedString << c;
		}
		if(c == '}') {
			writing = true;
			parsedString << variables[variableIndex];
			variableIndex++;
		}

	}

	return parsedString.str();
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