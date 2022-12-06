#include "WhenRule.h"
#include <vector>
#include <iostream>

WhenRule::WhenRule(std::vector<bool> cases, std::vector<rules::IRule*> list) : cases(cases), ruleList(list) {}

std::optional<vector<rules::IRule>> WhenRule::executeRule(GameModel model)
{
    std::vector<std::string> tokens = getTokens(failCondition);
    std::vector<dataVariant> variables;

    for(auto c : cases)
    {
        
    }
     return nullopt;
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