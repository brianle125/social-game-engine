#include <iostream>
#include <GameController.h>

#include "IRule.h"

using namespace std;

GameController::GameController(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience, GameModel gameModel) noexcept
	: name(gameName), minimumPlayers(gameMinimumPlayers), maximumPlayers(gameMaximumPlayers), audience(gameAudience), model(gameModel) {}

void GameController::printGame() {
	std::cout << "Name: " << name <<
		"\nMinimum Players: " << minimumPlayers <<
		"\nMaximum Players: " << maximumPlayers <<
		"\nAudience?: " << audience << "\n";
}


void GameController::addRule(std::unique_ptr<rules::IRule> rule) {
	rules.push_back(std::move(rule));
}

void GameController::executeRules() {
	for(auto const& rule : rules) {
		rule->executeRule();
	}
}