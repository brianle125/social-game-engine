#include "coinRule.h"


void CoinRule::setRuleName(string name){
    ruleName = name;
}

string CoinRule::getRuleName(){
    return ruleName;
}

void CoinRule::setlist(string str){
    list = str;
}

string CoinRule::getList(){
    return list;
}

void CoinRule::setFrom(string str){
    from = str;
}

string CoinRule::getFrom(){
    return from;
}

void CoinRule::setTo(string str){
    to = str;
}

string CoinRule::getTo(){
    return to;
}

void CoinRule::setCount(int num){
    count = num;
}

int CoinRule::getCount(){
    return count;
}

void CoinRule::setValue(string str){
    value = str;
}

string CoinRule::getValue(){
    return value;
}