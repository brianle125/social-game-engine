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

	controller.initializeStack();

	return controller;
}

GameModel GameCreator::createGameModel() {


	//parse and add variables here
	
	json constants = gameSource["constants"];
	json variables = gameSource["variables"];

	GameModel newGame;

	newGame.addConstantsFromJson(constants);
	newGame.addVariablesFromJson(variables);

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

	reverse(ruleList.begin(), ruleList.end());

	return ruleList;
}



