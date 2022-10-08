#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <GameCreator.h>
#include <Game.h>

using json = nlohmann::json;

using namespace std;

gameModel::Game GameCreator::createGame(std::string gameSpecification) {
	std::ifstream f(gameSpecification);
	json data = json::parse(f);

	cout << data.dump(4) << "\n";

	gameModel::Game newGame(data["configuration"]["name"].get<std::string>(),
				 data["configuration"]["player count"]["min"].get<int>(),
				 data["configuration"]["player count"]["min"].get<int>(),
				 data["configuration"]["audience"].get<bool>());


	return newGame;
}
