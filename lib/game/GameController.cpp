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
		//Parallel Processing
		if(parallelStacksActive()){
			for(auto& stack : parallelStacks) {
				processRuleFromStack(stack);
			}
			if(!parallelStacksActive()) {
				parallelStacks.clear();
			}
			return;
		}

		processRuleFromStack(ruleStack);	

	}
	catch (invalid_argument& e) {
		cout << "exception: " << e.what() << "\n";
		//do more error handling here
	}
}

bool GameController::parallelStacksActive() {
	for(auto& stack : parallelStacks) {
		if(stack.size() > 0) return true;
	}

	return false;
}

void GameController::processRuleFromStack(std::stack<rules::IRule*>& stack) {
	if(stack.empty()) return;

	//single processing
	auto rule = stack.top();
	auto newRules = rule->executeRule(model);

	RuleStatus status = rule->getStatus();

	if(status == FINISHED) {
		stack.pop();
	}
	//TODO: may need extra logic to deal with unfinished rules or rules awaiting input?
		
	//can probably use value_or somehow to skip this check but Im not sure how right now
	if(!newRules.has_value()) {
		return;
	}

	auto addRules = [& newRules](std::stack<rules::IRule*>& stack) {
		for(auto& newRule : *newRules) {
			cout << "new Rule\n";
			stack.push(&newRule);
		}
	};

	if(rule->isParallel()) {
		int stackCount = rule->getParallelCount();
		for(int i = 0; i < stackCount; i++) {
			std::stack<rules::IRule*> newStack;
			addRules(newStack);
			parallelStacks.push_back(newStack);
		}
		return;
	}

	addRules(stack);
}

bool GameController::isGameOver() noexcept {
	return ruleStack.empty();
	//return nextRule == rules.end();
}