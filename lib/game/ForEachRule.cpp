#include "include/IRule.h"
#include <vector>

using namespace std;

class ForEachRule final : public IRule
{
    public:
        rules::ForEachRule(vector<string> list, auto elem) : ruleList(list), elementObj(elem) {}

        void rules::executeRule() override
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
        auto elementObj; 
}