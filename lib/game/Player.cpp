#include "include/Player.h"

using namespace std;

Player::Player(string playerName) 
: name(playerName){}

void Player::addContent(string key, dataVariant content) {
    playerContents[key] = content;
}

dataVariant Player::getContent(string key) {
    return playerContents.find(key)->second;
}