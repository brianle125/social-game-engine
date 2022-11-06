#include "include/Player.h"

using namespace std;

Player::Player(string playerName) 
: name(playerName){}

void Player::addContent(string key, dataBucket content) {
    playerContents[key] = content;
}

dataBucket Player::getContent(string key) {
    return playerContents.find(key)->second;
}