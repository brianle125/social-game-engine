#pragma once

#include "IRule.h"
#include <string>

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(std::string c);
        ~WhenRule() override;
        void executeRule(GameModel model) override;
    private:
        std::string failCondition;
};