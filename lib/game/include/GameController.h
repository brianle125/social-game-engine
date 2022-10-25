#pragma once

#include <vector>
#include <memory>

#include "IRule.h"
#include "GameModel.h"

class GameController {
public:
    GameController(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience) noexcept;

    void printGame();

    //method to create List of Rules
    void addRule(std::unique_ptr<rules::IRule> rule);

    void executeRules();

private:
    
    
    const std::string name;
    const int minimumPlayers;
    const int maximumPlayers;
    const bool audience;

    GameModel model;
    //dictionary/map of setup

    std::vector<std::unique_ptr<rules::IRule>> rules;

};
