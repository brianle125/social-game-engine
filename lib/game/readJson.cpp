#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <nlohmann/json.hpp>
#include "coinGame.h"
using json = nlohmann::json;
using namespace std;

// The function takes the name of the Json file as a parameter
// It reads the file and inserts the values from the file to the associate class variable.
// The Game class object is returned
CoinGame readJsonFile(string fileName){
   // string fileName = "coin.json";
    std::ifstream f(fileName);
    json data = json::parse(f);
    CoinGame g1;

    //name
    g1.setName(data["configuration"]["name"]);

    //player num
    int min = data["configuration"]["player count"]["min"];
    int max = data["configuration"]["player count"]["max"];
    g1.setPlayerMin(min);
    g1.setPlayerMax(max);

    //audience
    bool bool_value = data["configuration"]["audience"];
    g1.setAudience(bool_value);

    //round
    int round = data["configuration"]["setup"]["Rounds"];
    g1.setRound(round);

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
    g1.setConstants(info);

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

    g1.setRules(rules);

    //info.setPlayerName(data["constants"]["coin"][0]);
    //g1.setConstants(info);
//    //variables
//    g1.setVariables(data["variables"]);
//    //rules
//    g1.setRules(data["rules"]);

    return g1;
}
int main() {
    try {
        string fileName = "coin.json";
        CoinGame g1 = readJsonFile( fileName);
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