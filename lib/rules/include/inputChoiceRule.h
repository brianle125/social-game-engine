#pragma once

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include "inputRule.h"
#include "Server.h"

using nlohmann::json;
using networking::Server;
using networking::Connection;

struct Player {
    Connection connection;
    bool init = false;

    Player(Connection c) : connection{c} {}
    Player() {}
};

class InputChoiceRule : public rules::InputRule {
public:
    Player target; // TODO: maybe change to Player class when implemented
    std::string prompt;
    std::vector<std::string> choices;
    std::string result;
    Server *server;
    int timeout;

    InputChoiceRule(std::string prompt, std::vector<std::string> choices, std::string result, Server* server, int timeout = 0);
    InputChoiceRule() {}

    void executeRule();
private:
    void validateArgs(json ruleConfig);
    void getInput() override;
    bool receiveResponse(std::string message) override;
};
