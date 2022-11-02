#include "include/WhenRule.h"
#include <vector>

using namespace std;

WhenRule::WhenRule(std::string c) : failCondition(con) {}
WhenRule::WhenRule(bool con) : condition(con) {}

void WhenRule::executeRule() 
{
    bool con = parseBooleanString(failCondition)
    if(condition)
    {
        //TODO: execute rule here
    }
}

