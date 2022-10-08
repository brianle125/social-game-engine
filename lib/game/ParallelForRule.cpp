#include "include/IRule.h"
#include <vector>

using namespace std;
class ParallelForRule : public IRule
{
    rules::ParallelForRule(vector<string> list) : ruleList(list) {}
    void rules::executeRule() override
    {
        for(unsigned idx = 0; idx < ruleList.size(); idx++)
        {
            //run rules sequentially in ruleList
        }
    }
    private:
        vector<string> ruleList;
};