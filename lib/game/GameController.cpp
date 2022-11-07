#include <iostream>
#include <GameController.h>

#include "ContentVariant.h"
#include "IRule.h"

using namespace std;

GameController::GameController(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, 
	bool gameAudience, GameModel gameModel) noexcept
	: name(gameName), minimumPlayers(gameMinimumPlayers), maximumPlayers(gameMaximumPlayers), 
	  audience(gameAudience), model(gameModel) {}

void GameController::printGame() {
	std::cout << "Name: " << name <<
		"\nMinimum Players: " << minimumPlayers <<
		"\nMaximum Players: " << maximumPlayers <<
		"\nAudience?: " << audience << "\n";
}


void GameController::addRule(std::unique_ptr<rules::IRule> rule) {
	rules.push_back(std::move(rule));
	nextRule = rules.begin();
}

void GameController::executeNextRule() {
	try {
		//double dereference, because nextRule is an iterator to unique_ptrs to rules
		rules::IRule& rule = *nextRule->get();
		rule.executeRule(model);
		nextRule++;
	}
	catch (std::invalid_argument& e) {
		std::cout << "exception: " << e.what() << "\n";
		//do more error handling here
	}

	//old implementation
	// for(auto const& rule : rules) {
	// 	rule->executeRule(model);
	// }
}

bool GameController::isGameOver() noexcept {
	return nextRule == rules.end();
}