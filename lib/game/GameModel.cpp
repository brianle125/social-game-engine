#include <iostream>
#include <stdexcept>
#include <GameModel.h>
#include <ContentVariant.h>

#include "IRule.h"

using namespace std;
using lookupKey = string;

void GameModel::addConstant(lookupKey key, dataVariant value) {
	constants.emplace(key, value);
}

void GameModel::addVariable(lookupKey key, dataVariant value) {
	variables.emplace(key, value);
}

dataVariant GameModel::getVariable(lookupKey key) {
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