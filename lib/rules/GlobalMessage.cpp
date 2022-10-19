#include <string>
#include "GlobalMessage.h"

#include <iostream>

GlobalMessage::GlobalMessage(std::string message)
    : message(message) {}

void GlobalMessage::executeRule() {
    std::cout << message << "\n";
}

