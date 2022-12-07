#include <string>
#include <GlobalMessage.h>

#include <iostream>

GlobalMessage::GlobalMessage(std::string message)
    : message(message) {}

optional<vector<rules::IRule>> GlobalMessage::executeRule(GameModel model) {
    //string_view view(message);

    std::cout << message << "\n";
    status = FINISHED;
    return nullopt;
}

