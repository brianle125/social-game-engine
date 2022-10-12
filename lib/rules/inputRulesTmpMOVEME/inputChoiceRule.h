#pragma once

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

class InputChoiceRule: public IRule {
public:
    Player::Player target;
    std::string prompt;
    std::vector<std::string> choices;
    std::string result;
    int timeout;

    InputChoiceRule(json ruleConfig);

    void executeRule() override;
    void validateArgs(json ruleConfig);
    void getInput(Server server);
    void receiveInput(std::string message);
private:
};