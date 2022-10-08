#include <GameCreator.h>

using namespace std;

//testing purposes
int
main() {
	GameCreator creator;
	std::string filename = "games/zen.json";
	creator.createGame(filename);
	return 0;
}