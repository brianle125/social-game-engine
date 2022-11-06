#include <iostream>

#include <GameModel.h>

#include "IRule.h"

using namespace std;

void GameModel::addConstant(std::string name, dataVariant value) {
	constants.emplace(name, value);
}

dataVariant GameModel::getConstant(std::string key) {
	return constants.find(key)->second;
}

void GameModel::addVariable(std::string name, dataVariant value) {
	variables.emplace(name, value);
}

dataVariant GameModel::getVariable(std::string key) {
	return variables.find(key)->second;
}

//set variables