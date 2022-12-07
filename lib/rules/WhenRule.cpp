#include "WhenRule.h"
#include <vector>
#include <iostream>

WhenRule::WhenRule(std::vector<bool> cases, std::vector<std::vector<rules::IRule*>> list) : cases(cases), rulesCollection(list) {}

std::optional<vector<rules::IRule>> WhenRule::executeRule(GameModel model)
{
    for(int i=0; i < cases.size(); i++)
    {
        //continue down if-else chain until true statement evaluated or end of list is reached
        //Needs to utilize expression parser to compare more concrete booleans
        if(cases.at(i) == false) {
            continue;
        } 
        else {
            for(auto rule : rulesCollection[i])
            {
                rule->executeRule(model);
            }
            break;
        }
        
    }
    status = FINISHED;
    return nullopt;
}