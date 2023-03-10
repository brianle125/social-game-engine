#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include "IRule.h"
#include "ContentVariant.h"
#include <optional>

class Reverse final : public rules::IRule {
private:
    std::string k;

public:
    Reverse(std::string key);
    ~Reverse() {}
    std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;
};