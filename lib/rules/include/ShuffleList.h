#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <optional>
#include "IRule.h"


class ShuffleList final : public rules::IRule {
    private:
        std::string k;
    
    public:
        ShuffleList(std::string key);
        ~ShuffleList() {}
        std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;
};