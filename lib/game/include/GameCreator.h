#pragma once

#include <fstream>
#include <Game.h>

class GameCreator {
public:

	//create game from JSON
	gameModel::Game createGame(std::string gameSpecification);
private:

	//JSON parser
	//ask client for setup input
};