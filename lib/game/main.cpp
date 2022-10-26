#include <GameCreator.h>
#include <IRule.h>
#include <iostream>
using namespace std;

//THIS IS A TESTING FUNCTION
int
main(int argc, char *argv[]) {
	std::string filename(argv[1]);
	GameCreator creator(filename);
	GameController newGame = creator.createGameController();
	newGame.printGame();

	// std::cout << boost::get<string>(newGame.getConstant("player-name")) << "\n";
	// std::cout << boost::get<int>(newGame.getVariable("wins")) << "\n";

	newGame.executeRules();
	return 0;
}