#include <iostream>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include "GameCreator.h"
#include "Game.h"

#include "GlobalMessage.h"

using json = nlohmann::json;

using namespace std;

GameCreator::GameCreator(std::string gameSpecification) {
	std::ifstream f(gameSpecification);
	gameSource = json::parse(f);

	GenerateRuleBuilders();

	//createGame();
}

gameModel::Game GameCreator::createGame() {

	json configData = gameSource["configuration"];

	gameModel::Game newGame(configData["name"].get<std::string>(),
				 configData["player count"]["min"].get<int>(),
				 configData["player count"]["min"].get<int>(),
				 configData["audience"].get<bool>());

	//parse and add variables here

	//parse and add rules here
	std::vector<std::unique_ptr<rules::IRule>> rules = createRules(gameSource);
	for(std::unique_ptr<rules::IRule> &rule : rules) {
		newGame.addRule(std::move(rule));
	}

	return newGame;
}

std::vector<std::unique_ptr<rules::IRule>> GameCreator::createRules(const json data) {
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



