#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include <fstream>
#include <Game.h>

#include "IRule.h"

class GameCreator {
public:
	GameCreator(std::string gameSpecification);

	//create game from JSON
	gameModel::Game createGame();
private:

	nlohmann::json gameSource;
	std::unordered_map<std::string, std::function<std::unique_ptr<rules::IRule> (nlohmann::json)>> ruleBuilders;
	void GenerateRuleBuilders();

	std::vector<std::unique_ptr<rules::IRule>> createRules(const nlohmann::json data);
	//ask client for setup input
};