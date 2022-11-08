#pragma once

#include <vector>
#include <stack>
#include <iterator>
#include <memory>

#include "IRule.h"
#include "GameModel.h"

class GameController {
public:
    GameController(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience, GameModel gameModel) noexcept;

    void printGame();

    //method to create List of Rules
    void addRule(std::unique_ptr<rules::IRule> rule);
    void initializeStack();

    void executeNextRule();
    bool isGameOver() noexcept;

private:
    const std::string name;
    const int minimumPlayers;
    const int maximumPlayers;
    const bool audience;

    GameModel model;
    //dictionary/map of setup
    std::stack<rules::IRule*> ruleStack;
    
    std::vector<std::unique_ptr<rules::IRule>> rules;
    // std::vector<std::unique_ptr<rules::IRule>>::iterator nextRule;

};
