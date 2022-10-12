#include "coinInfo.h"
#include <iostream>

using namespace std;

void CoinInfo::setCoinName(string str){
    coinName = str;
}

string CoinInfo::getCoinName(){
    return coinName;
}

void CoinInfo::setPlayerName(string str){
    playerName = str;
}

string CoinInfo::getPlayerName(){
    return playerName;
}