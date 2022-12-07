#pragma once

#include "IRule.h"
#include <string>
#include <optional>
#include "ContentVariant.h"
#include <vector>


class Add final : public rules::IRule
{
public:
    //add value parameter can be either integer literal or name of a variable or constant containing the value to add.
    Add(std::string key, dataVariant value);
    ~Add() {}
    std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;

private:
    std::string key;
    dataVariant val;
};
