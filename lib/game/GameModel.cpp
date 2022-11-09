#include <iostream>
#include <stdexcept>
#include <GameModel.h>
#include <ContentVariant.h>
#include "VariantParser.h"
#include "IRule.h"

using namespace std;
using lookupKey = string;

GameModel::GameModel() {
	parser = VariantParser();
}

void GameModel::addConstant(lookupKey key, dataVariant value) {
	constants.emplace(key, value);
}

void GameModel::addVariable(lookupKey key, dataVariant value) {
	variables.emplace(key, value);
}

dataVariant GameModel::getVariable(lookupKey key) {
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

void GameModel::setVariable(lookupKey key, dataVariant value) {
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