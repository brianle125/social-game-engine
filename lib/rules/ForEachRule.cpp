#include "include/ForEachRule.h"
#include <vector>
#include <iostream>


ForEachRule::ForEachRule(std::vector<rules::IRule> & list) : memberList(list) {}
ForEachRule::ForEachRule(std::string list) : listName(list) {}

void ForEachRule::executeRule(GameModel model) 
{
    //for every round from 1-n
    int totalRounds = model.getVariable("Rounds:");
    int currentRound = 1;


    while(currentRound <= totalRounds)
    {
        for(auto & rule: memberList)
        {
            rule.executeRule(model);
        }
    }
}