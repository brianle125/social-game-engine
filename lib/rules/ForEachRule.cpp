#include <ForEachRule.h>
#include <vector>
#include <iostream>


ForEachRule::ForEachRule(std::vector<rules::IRule*> list) : memberList(list) {}

std::optional<vector<rules::IRule>> ForEachRule::executeRule(GameModel model) 
{
    //TENTATIVE, OPEN TO REWORK
    //Execute each rule in the list for every round from 1 to n
    int totalRounds = std::get<int>(model.getVariable("Rounds"));
    int currentRound = std::get<int>(model.getVariable("upfrom"));

    while(currentRound < totalRounds)
    {
        for(auto & rule: memberList)
        {
            rule->executeRule(model);
        }
        currentRound++;
    }
    status = FINISHED;
    return nullopt;
}