#include "WhenRule.h"
#include <vector>
#include <iostream>

WhenRule::WhenRule(std::string c) : failCondition(c) {}
WhenRule::~WhenRule() {}

void WhenRule::executeRule(GameModel model) 
{
    bool condition = parseBooleanString(failCondition)
    if(condition)
    {
        //TODO: execute rule here
    }
}




