
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
    string constants;
    string variables;
    string rules;

public:
    void setName(string str);
    string getName();
    void setPlayerMin(int num);
    int getPlayerMin();
    void setPlayerMax(int num);
    int getPlayerMax();
    void setConstants(string str);
    string getConstants();
    void setVariables(string str);
    string getVariables();
    void setRules(string str);
    string getRules();
};