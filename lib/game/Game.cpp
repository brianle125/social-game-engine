
#include "Game.h"

using namespace std;

void gameMode::createRules()
{

}

void gameMode::update()
{
    
#include <iostream>
#include <Game.h>

using namespace std;

gameModel::Game::Game(std::string gameName, int gameMinimumPlayers, int gameMaximumPlayers, bool gameAudience) noexcept
	: name(gameName), minimumPlayers(gameMinimumPlayers), maximumPlayers(gameMaximumPlayers), audience(gameAudience) {}

void gameModel::Game::printGame() {
	std::cout << "Name: " << name <<
		"\nMinimum Players: " << minimumPlayers <<
		"\nMaximum Players: " << maximumPlayers <<
		"\nAudience?: " << audience << "\n";
}