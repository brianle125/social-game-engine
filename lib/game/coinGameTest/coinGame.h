#include "coinInfo.h"
#include "coinRule.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <exception>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
//class game

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
    CoinRule rules[3];

public:
    CoinGame();
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
    void setRules(CoinRule coinRule[]);
    CoinRule* getRules();
    void readJsonFile(string fileName);
};