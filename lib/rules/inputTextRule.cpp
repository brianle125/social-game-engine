#include "inputTextRule.h"

#include <iostream>

using networking::Message;
using networking::Response;

InputTextRule::InputTextRule(Player *target, std::string prompt, std::string result, Server* server, int timeout)
    : target{target}, prompt{prompt}, result{result}, server{server}, timeout{timeout} {
}

optional<vector<rules::IRule>> InputTextRule::executeRule(GameModel model) {
    this->model = model;

    std::string separator(": ");
    std::string msg = prompt + separator;

    getInput(target, msg);
}

void InputTextRule::getInput(Player *target, std::string msg) {
    Message message = { target->connection, msg};
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target->connection, Response{ this, std::chrono::system_clock::now() });
}

rules::InputRule::InputValidation InputTextRule::receiveResponse(std::string message, std::chrono::duration<double> duration) {
    std::cout << message << std::endl;
    if (timeout > 0 && duration.count() > timeout) { // TODO: Could change to use tickrate instead
    } else {
        model.addVariable(result, dataVariant(message));
    }
    return rules::InputRule::InputValidation::success;
}
