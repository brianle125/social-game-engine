#include "inputChoiceRule.h"

#include <typeinfo>
#include <iostream>

using networking::Message;

InputChoiceRule::InputChoiceRule(std::string prompt, std::vector<std::string> choices, std::string result, Server* server, int timeout)
    : prompt{prompt}, choices{choices}, result{result}, server{server}, timeout{timeout} {
}

optional<vector<rules::IRule>> InputChoiceRule::executeRule(GameModel model) { // base class may need to pass reference or pointer instead
    this->model = model;
    getInput();
}

// TODO: implement timer
void InputChoiceRule::getInput() {
    std::string choicesStr = std::accumulate(std::next(choices.begin()), choices.end(), choices[0],
        [] (const std::string &str1, const std::string &str2) {
            return str1 + ", " + str2;
        });
    std::string separator(": ");
    Message message = { target.connection, prompt + separator + choicesStr + "\n"};
    std::deque<Message> messages = { message };
    server->send(messages);
    server->awaitResponse(target.connection, this);
}

bool InputChoiceRule::receiveResponse(std::string message) {
    std::cout << message << std::endl;
    if (std::find(choices.begin(), choices.end(), message) != choices.end()) {
        std::cout << "CORRECT" << std::endl;
        return true;
    } else {
        std::cout << "pls try again" << std::endl;
        getInput();
        return false;
    }
}

// TODO: decide on validating args later
// void InputChoiceRule::validateArgs(json ruleConfig) {
//     if (typeid(ruleConfig["to"]) == typeid(std::string)) {
//         target = game.players[ruleConfig["to"]] ? game.players[ruleConfig["to"]] : NULL; // not sure how players should be stored
//         if (!target) {
//             // TODO: handle invalid, maybe use a helpful error msg
//         }
//     } else {
//         // TODO: handle invalid, maybe use a helpful error msg
//     }

//     if (typeid(ruleConfig["choices"]) == typeid(std::vector<std::string>)) {
//         choices = ruleConfig["choices"];
//     } else {
//         // TODO: handle invalid, maybe use a helpful error msg
//     }

//     if (typeid(ruleConfig["choices"]) == typeid(std::vector<std::string>)) {
//         choices = ruleConfig["choices"];
//     } else {
//         // TODO: handle invalid, maybe use a helpful error msg
//     }

//     if (typeid(ruleConfig["result"]) == typeid(std::string)) {
//         result = ruleConfig["result"];
//     } else {
//         // TODO: handle invalid, maybe use a helpful error msg
//     }

//     if (ruleConfig["timeout"] && typeid(ruleConfig["choices"]) == typeid(int)) {
//         timeout = ruleConfig["timeout"];
//     } else {
//         // TODO: handle invalid, maybe use a helpful error msg
//     }
// }
