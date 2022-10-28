#pragma once

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include "inputRule.h"
#include "IRule.h"
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

class InputVoteRule : public rules::InputRule, public rules::IRule {
public:
    Player target; // TODO: maybe change to Player class when implemented
    std::string prompt;
    std::vector<myVariant> choices;
    std::string result;
    Server *server;
    int timeout;

    InputVoteRule(std::string prompt, std::vector<myVariant> choices, std::string result, Server* server, int timeout = 0);
    InputVoteRule() {}

    void executeRule(GameModel model) override;
private:
    void validateArgs(json ruleConfig);
    void getInput() override;
    bool receiveResponse(std::string message, std::chrono::system_clock::time_point start) override;
};
