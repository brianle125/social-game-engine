#include <vector>
#include <string>

#include "IRule.h"
#include <nlohmann/json.hpp>

using nlohmann::json;


class ForEachRule final : public rules::IRule {
    public:
        ForEachRule(std::vector<rules::IRule> & list);
        ForEachRule(std::string lis);
        ~ForEachRule() {}
        std::optional<vector<rules::IRule>> executeRule(GameModel model);

    private:
        //list object to operate on, modify later
        std::vector<rules::IRule> memberList;
        std::string listName;
};