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

void CoinGame::setConstants(string str){
    constants = str;
}

string CoinGame::getConstants(){
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