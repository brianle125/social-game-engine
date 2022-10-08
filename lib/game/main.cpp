#include <GameCreator.h>
#include <IRule.h>
#include <iostream>
using namespace std;

//THIS IS A TESTING FUNCTION
int
main(int argc, char *argv[]) {
	GameCreator creator;
	std::string filename(argv[1]);
	gameModel::Game newGame = creator.createGame(filename);

	vector<string> list = {"test1"};
	ParallelForRule parallel(list);

	parallel.executeRule();
	newGame.printGame();
	return 0;
}