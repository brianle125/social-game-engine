#include "IRule.h"
#include <vector>
#include <string>

class LoopRule final: public rules::IRule
{
    public:
        LoopRule(vector<string>& list, bool con);
        void ExecuteRule() override;
        
    private:
        vector<string>& memberList;
        bool failCondition;
};