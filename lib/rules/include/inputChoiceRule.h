#pragma once

#include <map>
#include <string>
#include <vector>
#include <optional>

#include <nlohmann/json.hpp>
#include "inputRule.h"
#include "IRule.h"
#include "Server.h"
#include "Player.h"

using nlohmann::json;
using networking::Server;
using networking::Connection;

class InputChoiceRule final : public rules::InputRule, public rules::IRule {
public:
    Player *target; // TODO: maybe change to Player class when implemented
    std::string prompt;
    std::vector<dataVariant> choices;
    std::string result;
    Server *server;
    int timeout;

    GameModel model;

    InputChoiceRule(Player *target, std::string prompt, std::vector<dataVariant> choices, std::string result, Server *server, int timeout = 0);
    InputChoiceRule() {}

    optional<vector<rules::IRule>> executeRule(GameModel model) override;
private:
    void getInput() override;
    rules::InputRule::InputValidation receiveResponse(std::string message, std::chrono::system_clock::time_point start) override;
};
