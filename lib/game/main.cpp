#include <GameCreator.h>
#include <IRule.h>
#include <iostream>
#include <ContentVariant.h>
using namespace std;

//THIS IS A TESTING FUNCTION
int
main(int argc, char *argv[]) {
	std::string filename(argv[1]);
	GameCreator creator(filename);
	GameController newGame = creator.createGameController();
	newGame.printGame();

	//There is likely a better solution to this, but for now, this works
	while(!newGame.isGameOver()) {
		newGame.executeNextRule();
		
	}

	return 0;
}