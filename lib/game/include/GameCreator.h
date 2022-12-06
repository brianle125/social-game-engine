#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include <fstream>
#include <GameModel.h>
#include "GameController.h"

#include "IRule.h"

class GameCreator {
public:
	GameCreator(std::string gameSpecification);

	//create game from JSON
	GameController createGameController();
	void createRules(GameController& controller);

private:

	nlohmann::json gameSource;
	std::unordered_map<std::string, std::function<std::unique_ptr<rules::IRule> (nlohmann::json)>> ruleBuilders;

	GameModel createGameModel();
	void GenerateRuleBuilders();

	
	//ask client for setup input
};