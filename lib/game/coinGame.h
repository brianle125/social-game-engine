#include "coinInfo.h"
#include <string>
//class game
using namespace std;
class CoinGame{
private:
    string name;
    int playerMin;
    int playerMax;
    bool audience;
    int round;
    //constant in Json file is an array of objet
    //so create a class for constant
    CoinInfo constants[2];
    string variables;
    string rules;

public:
    void setName(string str);
    string getName();
    void setPlayerMin(int num);
    int getPlayerMin();
    void setPlayerMax(int num);
    int getPlayerMax();
    void setAudience(bool value);
    bool getAudience();
    void setRound(int num);
    int getRound();
    void setConstants(CoinInfo info[]);
    CoinInfo* getConstants();
    void setVariables(string str);
    string getVariables();
    void setRules(string str);
    string getRules();
};