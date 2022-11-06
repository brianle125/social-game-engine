#include <vector>
#include <string>

#include "IRule.h"


class ForEachRule final : public rules::IRule {
    public:
        ForEachRule(std::vector<myVariant> & list);
        ForEachRule(std::string list);
        ~ForEachRule() {}
        void executeRule(GameModel model) override;

    private:
        //list object to operate on, modify later
        std::vector<myVariant> memberList;
        std::string listName;
};