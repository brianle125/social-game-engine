#include <iostream>
#include <stack>
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

	dataVariant test = model.getVariable("player-name");
	cout << rva::visit(toStringVisitor{}, test) << "\n";

	test = model.getVariable("wins");
	cout << rva::visit(toStringVisitor{}, test) << "\n";
}


void GameController::addRule(std::unique_ptr<rules::IRule> rule) {
	rules.push_back(std::move(rule));
	//nextRule = rules.begin();
}

void GameController::initializeStack() {
	for(auto& rule : rules) {
		rules::IRule* rulePointer = rule.get();
		ruleStack.push(rulePointer);
	}
}

void GameController::executeNextRule() {
	try {
		auto rule = ruleStack.top();
		ruleStack.pop();
		auto newRules = rule->executeRule(model);
		//TODO: parallel rules need some kind of immediate processing most likely, 
		//or else rules need a way to mark themselves parallel and thus non-blocking

		//can probably use value_or somehow to skip this check but Im not sure how right now
		if(newRules.has_value()) {
			for(auto& newRule : *newRules) {
				cout << "new Rule\n";
				ruleStack.push(&newRule);
			}
		}
	}
	catch (invalid_argument& e) {
		cout << "exception: " << e.what() << "\n";
		//do more error handling here
	}
}

bool GameController::isGameOver() noexcept {
	return ruleStack.empty();
	//return nextRule == rules.end();
}