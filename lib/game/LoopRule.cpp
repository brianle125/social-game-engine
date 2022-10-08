using namespace std;
#include "IRule.h"
#include <vector>

class LoopRule final: public IRule
{
    public:
        LoopRule(vector<string> list, bool con) : ruleList(list), failCondition(con) {}
        void executeRule() override
        {
            int idx = 0;
            while(!failCondition && idx < ruleList.size())
            {
                //execute rules in the ruleList 
                //ruleList[idx].run();
                idx++;
            }
        }
    private:
        vector<string> ruleList;
        bool failCondition;
};