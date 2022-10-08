#include "inputChoiceRule.h"

#include <typeinfo>

InputChoiceRule::InputChoiceRule(json ruleConfig) {
    InputChoiceRule::validateArgs(ruleConfig);
}

void InputChoiceRule::executeRule() override {
    InputChoiceRule::getInput();
}

void InputChoiceRule::validateArgs(json ruleConfig) {
    if (typeid(ruleConfig["to"]) == typeid(std::string)) {
        target = game.players[ruleConfig["to"]] ? game.players[ruleConfig["to"]] : NULL; // not sure how players should be stored
        if (!target) {
            // TODO: handle invalid, maybe use a helpful error msg
        }
    } else {
        // TODO: handle invalid, maybe use a helpful error msg
    }

    if (typeid(ruleConfig["choices"]) == typeid(std::vector<std::string>)) {
        choices = ruleConfig["choices"];
    } else {
        // TODO: handle invalid, maybe use a helpful error msg
    }

    if (typeid(ruleConfig["choices"]) == typeid(std::vector<std::string>)) {
        choices = ruleConfig["choices"];
    } else {
        // TODO: handle invalid, maybe use a helpful error msg
    }

    if (typeid(ruleConfig["result"]) == typeid(std::string)) {
        result = ruleConfig["result"];
    } else {
        // TODO: handle invalid, maybe use a helpful error msg
    }

    if (ruleConfig["timeout"] && typeid(ruleConfig["choices"]) == typeid(int)) {
        timeout = ruleConfig["timeout"];
    } else {
        // TODO: handle invalid, maybe use a helpful error msg
    }
}

// TODO: implement the server code
void InputChoiceRule::getInput(Server server) {
    // might need to build string to also output choices
    auto message = server.messageBuilder(prompt);
    server.send(message);
}

void InputChoiceRule::receiveInput(std::string message) {
    Player[result]{result, message});
}