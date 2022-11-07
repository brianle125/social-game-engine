#include <vector>
#include <string>

#include "IRule.h"
#include <nlohmann/json.hpp>

using nlohmann::json;


class ForEachRule final : public rules::IRule {
    public:
        ForEachRule(std::vector<dataVariant> & list);
        ForEachRule(std::string list);
        ~ForEachRule() {}
        void executeRule(GameModel model) override;

    private:
        //list object to operate on, modify later
        std::vector<dataVariant> memberList;
        std::string listName;
};