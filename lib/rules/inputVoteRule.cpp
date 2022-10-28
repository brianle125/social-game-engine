#include "inputVoteRule.h"

#include <typeinfo>
#include <iostream>

using networking::Message;
using networking::Response;

InputVoteRule::InputVoteRule(std::string prompt, std::vector<myVariant> choices, std::string result, Server* server, int timeout)
    : prompt{prompt}, choices{choices}, result{result}, server{server}, timeout{timeout} {
}

void InputVoteRule::executeRule(GameModel model) {
    getInput();
}

void InputVoteRule::getInput() {
    std::string choicesStr = std::accumulate(std::next(choices.begin()), choices.end(), boost::get<std::string>(choices[0]),
        [] (const std::string str1, const myVariant &str2) {
            return str1 + ", " + boost::get<std::string>(str2);
        });
    std::string separator(": ");
    Message message = { target.connection, prompt + separator + choicesStr };
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target.connection, Response{ this, std::chrono::system_clock::now() });
}

bool InputVoteRule::receiveResponse(std::string message, std::chrono::system_clock::time_point start) {
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end-start;
    std::cout << message << std::endl;
    if (timeout > 0 && duration.count() > timeout) { // TODO: Could change to use tickrate instead
        return true;
    } else if (std::find(choices.begin(), choices.end(), message) != choices.end()) {
        return true;
    } else {
        getInput();
        return false;
    }
}
