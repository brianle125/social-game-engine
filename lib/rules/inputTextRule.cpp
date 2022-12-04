#include "inputTextRule.h"

#include <iostream>

using networking::Message;
using networking::Response;

InputTextRule::InputTextRule(Player *target, std::string prompt, std::string result, Server* server, int timeout)
    : target{target}, prompt{prompt}, result{result}, server{server}, timeout{timeout} {
}

optional<vector<rules::IRule>> InputTextRule::executeRule(GameModel model) {
    this->model = model;
    getInput();
}

void InputTextRule::getInput() {
    std::string separator(": ");
    Message message = { target->connection, prompt + separator};
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target->connection, Response{ this, std::chrono::system_clock::now() });
}

rules::InputRule::InputValidation InputTextRule::receiveResponse(std::string message, std::chrono::system_clock::time_point start) {
    std::cout << message << std::endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end-start;
    std::cout << message << std::endl;
    if (timeout > 0 && duration.count() > timeout) { // TODO: Could change to use tickrate instead
    } else {
        model.addVariable(result, dataVariant(message));
    }
    return rules::InputRule::InputValidation::success;
}
