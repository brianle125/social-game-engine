#include "include/ForEachRule.h"
#include <vector>

using namespace std;

ForEachRule::ForEachRule(vector<string> & list) : ruleList(list) {}

void ForEachRule::ExecuteRule() 
{
    for(auto rule: ruleList)
    {
        //execute rule; todo
    }
}