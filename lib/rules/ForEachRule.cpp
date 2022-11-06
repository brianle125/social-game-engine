#include "include/ForEachRule.h"
#include <vector>
#include <iostream>


ForEachRule::ForEachRule(std::vector<myVariant> & list) : memberList(list) {}
ForEachRule::ForEachRule(std::string list) : listName(list) {}

void ForEachRule::executeRule(GameModel model) 
{
    for(auto rule: memberList)
    {
        rule.executeRule();
    }
}