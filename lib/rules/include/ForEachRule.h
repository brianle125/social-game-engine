#include "IRule.h"

#include <vector>
#include <string>
//#include <nlohmann/json.hpp>

//using nlohmann::json;


class ForEachRule final : public rules::IRule {
    public:
        ForEachRule(std::vector<rules::IRule*> list);
        ~ForEachRule() {}
        std::optional<vector<rules::IRule>> executeRule(GameModel model) override;

    private:
        //list object to operate on, modify later
        std::vector<rules::IRule*> memberList;
};