#include "coinGame.h"
#include <iostream>

using namespace std;
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

void CoinGame::setRules(string str){
    rules = str;
}

string CoinGame::getRules(){
    return rules;
}

//int main(){
//    CoinGame game;
//    game.setConstants("hi");
//    cout<<game.getConstants();
//}