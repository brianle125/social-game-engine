#include "WhenRule.h"
#include <vector>
#include <iostream>

WhenRule::WhenRule(std::string c) : failCondition(c) {}

void WhenRule::executeRule(GameModel model) 
{
    std::vector<std::string> tokens = getTokens(failCondition);
    std::vector<dataVariant> variables;

    
    for(auto & token : tokens)
    {
        dataVariant var = model.getVariable(token);
        variables.push_back(var);
    }

    //initialize boolean from variables; subject to rework
    bool condition;

    if(condition)
    {
        //TODO: execute rule(s) here
    }
}

//handle brackets later
std::vector<std::string> WhenRule::getTokens(std::string str)
{
    std::vector<std::string> tokens;
    tokens.reserve(str.size());

    const char delim = '.';

    int startPos = 0;
    int endPos = -1;

    for (int i= 0; i < str.size(); i++)
    {
        if (str[i] == delim || str[i] == ' ')
        {
            startPos = endPos;
            endPos = i;
            int index = startPos + 1;
            int length = endPos - index;

            std::string token(str.data() + index, length);
            tokens.push_back(token);
        }
    }
    return tokens;
    
}