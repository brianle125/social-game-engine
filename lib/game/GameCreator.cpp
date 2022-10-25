#include <iostream>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include "GameCreator.h"
#include "GameModel.h"

using json = nlohmann::json;

using namespace std;

GameCreator::GameCreator(std::string gameSpecification) {
	std::ifstream f(gameSpecification);
	gameSource = json::parse(f);

	GenerateRuleBuilders();
}

GameController GameCreator::createGameController() {
	json configData = gameSource["configuration"];

	GameModel model = createGameModel();

	GameController controller(configData["name"],
							  configData["player count"]["min"],
							  configData["player count"]["max"],
							  configData["audience"],
							  model);

	auto rulesList = createRules();

	for(auto &rule : rulesList) {
		controller.addRule(std::move(rule));
	}

	return controller;
}

GameModel GameCreator::createGameModel() {

	GameModel newGame;

	//parse and add variables here
	/*
	json constants = gameSource["constants"];
	for(auto constant : constants.items()) {
		std::string keyname = constant.key();
		std::string valuename = constant.value();
		myVariant variant = valuename;

		newGame.addConstant(keyname, variant);
	}

	json variables = gameSource["variables"];
	for(auto variable : variables.items()) {
		std::string keyname = variable.key();
		int valuename = variable.value();
		myVariant variant = valuename;

		newGame.addVariable(keyname, variant);
	}
	*/

	return newGame;
}

std::vector<std::unique_ptr<rules::IRule>> GameCreator::createRules() {
	json rules = gameSource["rules"];

	std::vector<std::unique_ptr<rules::IRule>> ruleList;
	ruleList.reserve(rules.size());

	for(auto rule : rules) {
		auto ruleBuilder = ruleBuilders.find(rule["rule"]);
		if(ruleBuilder != ruleBuilders.end()) {
			auto newRule = ruleBuilder->second(rule);
			ruleList.push_back(std::move(newRule));
		}
	}

	return ruleList;
}



