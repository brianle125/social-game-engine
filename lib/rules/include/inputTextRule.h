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

class InputTextRule : public rules::InputRule {
public:
    Player target; // TODO: maybe change to Player class when implemented
    std::string prompt;
    std::string result;
    Server *server;
    int timeout;

    InputTextRule(std::string prompt, std::string result, Server* server, int timeout = 0);
    InputTextRule() {}

    void executeRule();
private:
    void validateArgs(json ruleConfig);
    void getInput() override;
    bool receiveResponse(std::string message) override;
};