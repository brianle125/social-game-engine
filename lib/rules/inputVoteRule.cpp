#include "inputVoteRule.h"

#include <typeinfo>
#include <iostream>

using networking::Message;
using networking::Response;

InputVoteRule::InputVoteRule(Player *target, std::string prompt, std::vector<dataVariant> choices, std::string result, Server* server, int timeout)
    : target{target}, prompt{prompt}, choices{choices}, result{result}, server{server}, timeout{timeout} {
}

optional<vector<rules::IRule>> InputVoteRule::executeRule(GameModel model) {
    this->model = model;
    getInput();
}

void InputVoteRule::getInput() {
    dataVariant choicesVariant(choices);
    std::string choicesStr = rva::visit(toStringVisitor{}, choicesVariant);
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
    } else if (std::find(choices.begin(), choices.end(), dataVariant(message)) != choices.end()) {
        // the invariant currently doesn't support maps so can't store a map of { "choice": int }
        // currently storing each choice as a 1D key : value which might conflict with
        // keys that share the same name
        int voteCount = rva::visit(toIntVisitor{}, model.getVariable(message));
        model.setVariable(message, dataVariant(voteCount+1));
        return rules::InputRule::InputValidation::success;
    } else {
        getInput();
        return rules::InputRule::InputValidation::failure;
    }
}
