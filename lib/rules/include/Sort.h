#pragma once

#include <vector>
#include "IRule.h"
#include <optional>
#include <string>

class Sort final : public rules::IRule{
    public:
        Sort(std::string key);
        Sort(std::string key, std::string sortingKey);
        ~Sort() {}
        std::optional<std::vector<rules::IRule>> executeRule(GameModel model) override;

    private:
       std::string key;
       std::string sortingKey;
};