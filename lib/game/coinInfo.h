
#include <string>
//class game
using namespace std;
class CoinInfo{
private:
    string coinName;
    string playerName;

public:
    void setCoinName(string str);
    string getCoinName();
    void setPlayerName(string str);
    string getPlayerName();
};