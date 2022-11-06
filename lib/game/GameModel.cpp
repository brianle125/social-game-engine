#include <iostream>

#include <GameModel.h>

#include "IRule.h"

using namespace std;

void GameModel::addConstant(std::string name, dataBucket value) {
	constants.emplace(name, value);
}

dataBucket GameModel::getConstant(std::string key) {
	return constants.find(key)->second;
}

void GameModel::addVariable(std::string name, dataBucket value) {
	variables.emplace(name, value);
}

dataBucket GameModel::getVariable(std::string key) {
	return variables.find(key)->second;
}

//set variables