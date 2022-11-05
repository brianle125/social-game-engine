#include "inputVoteRule.h"

#include <typeinfo>
#include <iostream>

using networking::Message;
using networking::Response;

InputVoteRule::InputVoteRule(Player *target, std::string prompt, std::vector<myVariant> choices, std::string result, Server* server, int timeout)
    : target{target}, prompt{prompt}, choices{choices}, result{result}, server{server}, timeout{timeout} {
}

void InputVoteRule::executeRule(GameModel model) {
    getInput();
}

void InputVoteRule::getInput() {
    toStringVisitor stringVisitor;
    std::string choicesStr = stringVisitor(choices);
    std::string separator(": ");
    Message message = { target->connection, prompt + separator + choicesStr };
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target->connection, Response{ this, std::chrono::system_clock::now() });
}

rules::InputRule::InputValidation InputVoteRule::receiveResponse(std::string message, std::chrono::system_clock::time_point start) {
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end-start;
    std::cout << message << std::endl;
    if (timeout > 0 && duration.count() > timeout) { // TODO: Could change to use tickrate instead
        return rules::InputRule::InputValidation::success;
    } else if (std::find(choices.begin(), choices.end(), message) != choices.end()) {
        return rules::InputRule::InputValidation::success;
    } else {
        getInput();
        return rules::InputRule::InputValidation::failure;
    }
}
