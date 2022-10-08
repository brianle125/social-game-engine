#include "include/LoopRule.h"
#include <vector>

using namespace std;

LoopRule::LoopRule(vector<string>& list, bool con) : ruleList(list), failCondition(con) {}

void LoopRule::ExecuteRule() 
{
    int idx = 0;
    while(!failCondition && idx < ruleList.size())
    {
        //execute rules in the ruleList 
        //ruleList[idx].run();
        idx++;
    }
}