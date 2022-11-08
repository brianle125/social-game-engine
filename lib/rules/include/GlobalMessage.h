#pragma once
#include "IRule.h"
#include <string>
#include <optional>

class GlobalMessage final : public rules::IRule {   
public:
    GlobalMessage(string message);
    optional<vector<rules::IRule>> executeRule(GameModel model) override;

private:
    string message;
};