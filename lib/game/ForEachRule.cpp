using namespace std;
#include "IRule.h"

class ForEachRule final : public IRule
{
    public:
        ForEachRule(vector<string> list) : ruleList(list) {}

        void executeRule() override
        {
            for(auto rule: ruleList)
            {
                //execute some rule
                rule.run();
            }
        }

    private:
        //list object to operate on
        vector<string> ruleList;
}