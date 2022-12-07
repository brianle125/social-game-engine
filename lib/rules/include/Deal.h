#pragma once

#include <vector>
#include <string>
#include "IRule.h"
#include "ContentVariant.h"
#include <optional>

class Deal final : public rules::IRule {
private:
    std::string from_key;
    std::string to_key;
    int count;

public:
    Deal(std::string from, std::string to, int count);
    ~Deal() {}
    std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;
};