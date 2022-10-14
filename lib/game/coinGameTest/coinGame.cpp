#include "coinGame.h"

#include <iostream>

using namespace std;
CoinGame::CoinGame(){
    //path from bin to coin.json
    string file_path = "../games/coin.json";
    readJsonFile(file_path);
}

void CoinGame::setName(string str){
    name = str;
}

string CoinGame::getName(){
    return name;
}

void CoinGame::setPlayerMin(int num){
    playerMin = num;
}

int CoinGame::getPlayerMin(){
    return playerMin;
}

void CoinGame::setPlayerMax(int num){
    playerMax = num;
}

int CoinGame::getPlayerMax(){
    return playerMax;
}

void CoinGame::setAudience(bool value){
    audience = value;
}
void CoinGame::setRound(int num){
    round = num;
}
int CoinGame::getRound(){
    return round;
}
bool CoinGame::getAudience(){
    return audience;
}

void CoinGame::setConstants(CoinInfo info[]){
    constants[0] = info[0];
    constants[1] = info[1];
}

CoinInfo* CoinGame::getConstants(){
    return constants;
}

void CoinGame::setVariables(string str){
    variables = str;
}

string CoinGame::getVariables(){
    return variables;
}

void CoinGame::setRules(CoinRule coinRule[]){
    rules[0] = coinRule[0];
    rules[1] = coinRule[1];
    rules[2] = coinRule[2];
}

CoinRule* CoinGame::getRules(){
    return rules;
}


// The function takes the name of the Json file as a parameter
// It reads the file and inserts the values from the file to the class variable.
void CoinGame::readJsonFile(string fileName){
    // string fileName = "coin.json";
    std::ifstream f(fileName);
    cout << "1" << endl;
    json data = json::parse(f);
    cout << "2" << endl;

    //name
    setName(data["configuration"]["name"]);

    //player num
    int min = data["configuration"]["player count"]["min"];
    int max = data["configuration"]["player count"]["max"];
    setPlayerMin(min);
    setPlayerMax(max);

    //audience
    bool bool_value = data["configuration"]["audience"];
    setAudience(bool_value);

    //round
    int round = data["configuration"]["setup"]["Rounds"];
    setRound(round);

    //constants
    CoinInfo info[2];
    string coin_name_1 = data["constants"]["coin"][0]["name"];
    info[0].setCoinName(coin_name_1);
    string player_name_1 = data["constants"]["coin"][0]["player"];
    info[0].setPlayerName(player_name_1);

    string coin_name_2 = data["constants"]["coin"][1]["name"];
    info[1].setCoinName(coin_name_2);
    string player_name_2 = data["constants"]["coin"][1]["player"];
    info[1].setPlayerName(player_name_2);
    setConstants(info);

    //rules
    CoinRule rules[3];
    rules[0].setRuleName(data["rules"][0]["rule"]);
    rules[0].setlist(data["rules"][0]["List"]);

    rules[1].setRuleName(data["rules"][1]["rule"]);
    rules[1].setFrom(data["rules"][1]["from"]);
    rules[1].setTo(data["rules"][1]["to"]);
    rules[1].setCount(data["rules"][1]["count"]);

    rules[2].setRuleName(data["rules"][2]["rule"]);
    rules[2].setValue(data["rules"][2]["value"]);

    setRules(rules);
}

int main() {
    try {
        CoinGame g1;
        cout<< ""<<g1.getName()<<endl;
        cout<< ""<<g1.getPlayerMin()<<endl;
        cout<< ""<<g1.getPlayerMax()<<endl;
        cout<<""<<g1.getAudience()<<endl;
        cout<<""<<g1.getRound()<<endl;


        cout<<""<<g1.getConstants()[0].getCoinName()<<endl;
        cout<<""<<g1.getConstants()[0].getPlayerName()<<endl;
        cout<<""<<g1.getConstants()[1].getCoinName()<<endl;
        cout<<""<<g1.getConstants()[1].getPlayerName()<<endl;

        cout<<""<<g1.getRules()[0].getRuleName()<<endl;
        cout<<""<<g1.getRules()[0].getList()<<endl;

        cout<<""<<g1.getRules()[1].getRuleName()<<endl;
        cout<<""<<g1.getRules()[1].getFrom()<<endl;
        cout<<""<<g1.getRules()[1].getTo()<<endl;
        cout<<""<<g1.getRules()[1].getCount()<<endl;

        cout<<""<<g1.getRules()[2].getRuleName()<<endl;
        cout<<""<<g1.getRules()[2].getValue()<<endl;

        return 0;
    }
    catch (exception &e) {
        cout << "exception" << e.what() << endl;
        return -1;
    }
}