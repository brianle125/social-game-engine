
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <GameCreator.h>

using json = nlohmann::json;

using namespace std;

void GameCreator::createGame(std::string gameSpecification) {
	std::ifstream f(gameSpecification);
	json data = json::parse(f);

	cout << data.dump(4) << "\n";
	cout << data["configuration"]["name"] << "\n";
}