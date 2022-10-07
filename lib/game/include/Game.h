#pragma once

namespace gameModel {

	class Game {
	public:
		const std::string name;
		const int minimumPlayers;
		const int maximumPlayers;

		Game(std::string n, int min, int max, bool aud) : name(n), minimumPlayers(min), 
			maximumPlayers(max), audience(aud) {}  
		~Game();

		void createRules();
		void update();

	private:
		
		
		//list of Players
		const bool audience;
		//dictionary of setup

		//dictionary of constants
		
		//dictionary of variables
		 
		//List of Rules

	};
}