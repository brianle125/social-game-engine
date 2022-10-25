#include <iostream>

#include <GameModel.h>

#include "IRule.h"

using namespace std;



void GameModel::addConstant(std::string name, myVariant value) {
	constants.emplace(name, value);
}

myVariant GameModel::getConstant(std::string key) {
	return constants.find(key)->second;
}

void GameModel::addVariable(std::string name, myVariant value) {
	variables.emplace(name, value);
}

myVariant GameModel::getVariable(std::string key) {
	return variables.find(key)->second;
}

//set variables