#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include "IRule.h"
#include "ContentVariant.h"
#include <optional>

class Reverse final : public rules::IRule {
private:
    //vector<string> list;
    std::string k;

public:
    //vector<string> getList();
    Reverse(std::string key);
    ~Reverse() {}
    std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;
    //void setList(vector<string> newList);
    //void reverseList();
};