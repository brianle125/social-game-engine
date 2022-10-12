#pragma once

namespace gameModel {

	class Game {
	public:
		const std::string name;
		const int minimumPlayers;
		const int maximumPlayers;

		Game(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience) noexcept;

		void printGame();
		 
		//method to create List of Rules

	private:
		
		
		//list of Players
		const bool audience;
		//dictionary of setup

		//dictionary of constants
		//dictionary of variables
		 
		//std::vector<IRule> rules;

	};
}