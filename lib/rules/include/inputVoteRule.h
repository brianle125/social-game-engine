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

class InputVoteRule final : public rules::InputRule, public rules::IRule {
public:
    Player *target; // TODO: maybe change to Player class when implemented
    std::string prompt;
    std::vector<myVariant> choices;
    std::string result;
    Server *server;
    int timeout;

    InputVoteRule(Player *target, std::string prompt, std::vector<myVariant> choices, std::string result, Server* server, int timeout = 0);

    void executeRule(GameModel model) override;
private:
    void getInput() override;
    rules::InputRule::InputValidation receiveResponse(std::string message, std::chrono::system_clock::time_point start) override;
};
