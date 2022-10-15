#pragma once

#include <map>
#include <string>

#include <nlohmann/json.hpp>

class InputTextRule: public IRule {
public:
    Player::Player target;
    std::string prompt;
    std::string result;
    int timeout;

    InputTextRule(json ruleConfig);

    void executeRule() override;
    void validateArgs(json ruleConfig);
    void getInput(Server server);
    void receiveInput(std::string message);
private:
};