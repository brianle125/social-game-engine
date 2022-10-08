#include "inputTextRule.h"

#include <typeinfo>

InputTextRule::InputTextRule(json ruleConfig) {
    InputTextRule::validateArgs(ruleConfig);
}

void InputTextRule::executeRule() override {
    InputTextRule::getInput();
}

void InputTextRule::validateArgs(json ruleConfig) {
}

void InputTextRule::getInput(Server server) {
}

void InputTextRule::receiveInput(std::string message) {
}