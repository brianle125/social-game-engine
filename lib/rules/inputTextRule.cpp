#include "inputTextRule.h"

#include <iostream>

using networking::Message;

InputTextRule::InputTextRule(std::string prompt, std::string result, Server* server, int timeout)
    : prompt{prompt}, result{result}, server{server}, timeout{timeout} {
}

void InputTextRule::executeRule() {
    getInput();
}

// TODO: implement timer
void InputTextRule::getInput() {
    std::string separator(": ");
    Message message = { target.connection, prompt + separator};
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target.connection, this);
}

bool InputTextRule::receiveResponse(std::string message) {
    std::cout << message << std::endl;
    return true;
}
