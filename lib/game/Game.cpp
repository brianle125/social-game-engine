#include <iostream>
#include <Game.h>

#include "IRule.h"

gameModel::Game::Game(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience) noexcept
	: name(gameName), minimumPlayers(gameMinimumPlayers), maximumPlayers(gameMaximumPlayers), audience(gameAudience) {}

void gameModel::Game::printGame() {
	std::cout << "Name: " << name <<
		"\nMinimum Players: " << minimumPlayers <<
		"\nMaximum Players: " << maximumPlayers <<
		"\nAudience?: " << audience << "\n";
}

void gameModel::Game::addConstant(std::string name, myVariant value) {
	constants.emplace(name, value);
}

myVariant gameModel::Game::getConstant(std::string key) {
	return constants.find(key)->second;
}

void gameModel::Game::addVariable(std::string name, myVariant value) {
	variables.emplace(name, value);
}

myVariant gameModel::Game::getVariable(std::string key) {
	return variables.find(key)->second;
}

void gameModel::Game::addRule(std::unique_ptr<rules::IRule> rule) {
	rules.push_back(std::move(rule));
}

void gameModel::Game::executeRules() {
	for(auto const& rule : rules) {
		rule->executeRule();
	}
}