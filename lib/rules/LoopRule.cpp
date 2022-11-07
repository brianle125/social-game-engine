#include "include/LoopRule.h"
#include <vector>

using namespace std;

LoopRule::LoopRule(vector<dataVariant>& memberList, bool con) : memberList(list), failCondition(con) {}

void LoopRule::executeRule(GameModel model) 
{
    int idx = 0;
    while(!failCondition && idx < memberList.size())
    {
        //execute rules in the ruleList 
        memberList[idx].executeRule();
        idx++;
    }
}