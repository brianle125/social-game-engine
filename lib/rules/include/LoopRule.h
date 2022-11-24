#include "include/IRule.h"
#include <vector>
#include <string>

class LoopRule final: public rules::IRule
{
    public:
        LoopRule(std::vector<rules::IRule>& list, bool con);
        std::optional<vector<rules::IRule>> executeRule(GameModel model) override;
        
    private:
        std::vector<rules::IRule> memberList;
        bool failCondition;
};