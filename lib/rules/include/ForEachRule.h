#include <vector>
#include <string>

#include "IRule.h"


class ForEachRule final : public rules::IRule {
    public:
        ForEachRule(std::vector<string> & list);
        ~ForEachRule() {}
        void executeRule(GameModel model) override;

    private:
        //list object to operate on, modify later
        std::vector<std::string> memberList;
};