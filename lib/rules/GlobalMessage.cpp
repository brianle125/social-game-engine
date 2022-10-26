#include <string>
#include "GlobalMessage.h"

#include <iostream>

GlobalMessage::GlobalMessage(std::string message)
    : message(message) {}

void GlobalMessage::executeRule(GameModel model) {
    std::cout << message << "\n";
}

