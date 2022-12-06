#pragma once

#include <map>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include "inputRule.h"
#include "IRule.h"
#include "Server.h"
#include "Player.h"

using nlohmann::json;
using networking::Server;
using networking::Connection;

class InputChoiceRule : public rules::InputRule, public rules::IRule {
public:
    Player *target;
    std::string prompt;
    std::vector<dataVariant> choices;
    std::string result;
    Server *server;
    int timeout;

    GameModel model;

    InputChoiceRule(Player *target, std::string prompt, std::vector<dataVariant> choices, std::string result, Server *server, int timeout = 0);
    InputChoiceRule() {}

    optional<vector<rules::IRule>> executeRule(GameModel model) override;

    virtual void getInput(Player *target, std::string msg);
    rules::InputRule::InputValidation receiveResponse(std::string message, std::chrono::duration<double> duration) override;
};
