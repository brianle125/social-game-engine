#include <iostream>
#include <stdexcept>
#include <GameModel.h>
#include <ContentVariant.h>

#include "IRule.h"

using namespace std;

void GameModel::addConstant(std::string name, dataVariant value) {
	constants.emplace(name, value);
}

void GameModel::addVariable(std::string name, dataVariant value) {
	variables.emplace(name, value);
}

dataVariant GameModel::getVariable(std::string key) {
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

void GameModel::setVariable(std::string key, dataVariant value) {
	auto varToUpdate = variables.find(key);
	if(varToUpdate != variables.end()) {
		varToUpdate->second = value;
		return;
	}

	//TODO: this may need to be replaced with implicit creation
	throw std::invalid_argument("Variable " + key + " Not Found");
}