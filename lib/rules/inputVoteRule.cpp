#include "inputChoiceRule.h"

#include <typeinfo>
#include <iostream>

using networking::Message;

InputChoiceRule::InputChoiceRule(std::string prompt, std::vector<std::string> choices, std::string result, Server* server, int timeout)
    : prompt{prompt}, choices{choices}, result{result}, server{server}, timeout{timeout} {
}

void InputChoiceRule::executeRule() {
    getInput();
}

// TODO: implement timer
void InputChoiceRule::getInput() {
    std::string choicesStr = std::accumulate(std::next(choices.begin()), choices.end(), choices[0],
        [] (const std::string &str1, const std::string &str2) {
            return str1 + ", " + str2;
        });
    std::string separator(": ");
    Message message = { target.connection, prompt + separator + choicesStr };
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target.connection, this);
}

bool InputChoiceRule::receiveResponse(std::string message) {
    std::cout << message << std::endl;
    if (std::find(choices.begin(), choices.end(), message) != choices.end()) {
        std::cout << "OKAY" << std::endl;
        return true;
    } else {
        std::cout << "pls try again" << std::endl;
        getInput();
        return false;
    }
}
