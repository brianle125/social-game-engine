#include <string>
#include "GlobalMessage.h"

#include <iostream>

GlobalMessage::GlobalMessage(std::string message)
    : message(message) {}

void GlobalMessage::executeRule(GameModel model) {
    string_view view(message);

    std::cout << message << "\n";
}

