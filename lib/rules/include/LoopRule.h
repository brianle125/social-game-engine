#include "include/IRule.h"
#include <vector>
#include <string>

class LoopRule final: public rules::IRule
{
    public:
        LoopRule(std::vector<myVariant>& list, bool con);
        void executeRule(GameModel model) override;
        
    private:
        std::vector<myVariant> memberList;
        bool failCondition;
};