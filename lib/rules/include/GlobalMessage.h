#pragma once
#include "IRule.h"
#include <string>

class GlobalMessage final : public rules::IRule {   
public:
    GlobalMessage(std::string message);
    void executeRule(GameModel model) override;

private:
    std::string message;
};