#include "inputChoiceRule.h"

#include <typeinfo>
#include <iostream>

using networking::Message;
using networking::Response;

InputChoiceRule::InputChoiceRule(Player *target, std::string prompt, std::vector<dataVariant> choices, std::string result, Server *server, int timeout)
    : target{target}, prompt{prompt}, choices{choices}, result{result}, server{server}, timeout{timeout} {
        this->choices = choices;
}

optional<vector<rules::IRule>> InputChoiceRule::executeRule(GameModel model) { // base class may need to pass reference or pointer instead
    this->model = model;

    dataVariant choicesVariant(choices);
    std::string choicesStr = rva::visit(toStringVisitor{}, choicesVariant);
    std::string separator(": ");
    std::string msg = prompt + separator + choicesStr + "\n";

    getInput(target, msg);
}

void InputChoiceRule::getInput(Player *target, std::string msg) {
    Message message = { target->connection, msg };
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target->connection, Response{ this, std::chrono::system_clock::now() });
}

rules::InputRule::InputValidation InputChoiceRule::receiveResponse(std::string message, std::chrono::duration<double> duration) {
    std::cout << message << std::endl;
    if (timeout > 0 && duration.count() > timeout) { // TODO: Could change to use tickrate instead
        return rules::InputRule::InputValidation::success;
    } else if (std::find(choices.begin(), choices.end(), dataVariant(message)) != choices.end()) {
        model.addVariable(result, dataVariant(message));
        return rules::InputRule::InputValidation::success;
    } else {
        dataVariant choicesVariant(choices);
        std::string choicesStr = rva::visit(toStringVisitor{}, choicesVariant);
        std::string separator(": ");
        std::string msg = prompt + separator + choicesStr + "\n";

        // set timeout to remaining time
        // TODO: Change timeout to double to avoid roundoff
        timeout = timeout - duration.count();
        getInput(target, msg);
        return rules::InputRule::InputValidation::failure;
    }
}
