#include <iostream>
#include <Game.h>

#include "IRule.h"

using namespace std;

gameModel::Game::Game(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience) noexcept
	: name(gameName), minimumPlayers(gameMinimumPlayers), maximumPlayers(gameMaximumPlayers), audience(gameAudience) {}

void gameModel::Game::printGame() {
	std::cout << "Name: " << name <<
		"\nMinimum Players: " << minimumPlayers <<
		"\nMaximum Players: " << maximumPlayers <<
		"\nAudience?: " << audience << "\n";
}

void gameModel::Game::addRule(std::unique_ptr<rules::IRule> rule) {
	rules.push_back(std::move(rule));
}

void gameModel::Game::executeRules() {
	for(auto const& rule : rules) {
		rule->executeRule();
	}
}