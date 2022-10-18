#pragma once

#include <vector>
#include <memory>

#include "IRule.h"
#include "ContentVariant.h"

namespace gameModel {

	class Game {
	public:
		const std::string name;
		const int minimumPlayers;
		const int maximumPlayers;

		Game(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience) noexcept;

		void printGame();

		void addConstant(std::string name, myVariant value);

		//method to create List of Rules
		void addRule(std::unique_ptr<rules::IRule> rule);

		void executeRules();

	private:
		
		
		//list of Players
		const bool audience;
		//dictionary of setup

		std::unordered_map<std::string, myVariant> constants;
		std::unordered_map<std::string, myVariant> variables;

		std::vector<std::unique_ptr<rules::IRule>> rules;

	};
}