#include "include/Player.h"

using namespace std;

Player::Player(string playerName) 
: name(playerName){}

void Player::addContent(string key, myVariant content) {
    playerContents[key] = content;
}

myVariant Player::getContent(string key) {
    return playerContents.find(key)->second;
}