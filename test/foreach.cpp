#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ForEachRule.h"
#include "GlobalMessage.h"


/** 
 * This section of tests simulate game construction 
 * through Gamemodel directly rather than through
 * JSON game construction. 
 */

TEST(ForEachRuleSuite, oneRoundBasicRules)
{
    GameModel model;
    model.addVariable("Rounds", 1);

    std::vector<rules::IRule*> rules;
    rules.emplace_back(std::make_unique<GlobalMessage>("first"));
    rules.emplace_back(std::make_unique<GlobalMessage>("second"));
    rules.emplace_back(std::make_unique<GlobalMessage>("third"));
    ForEachRule foreach(rules);
    foreach.executeRule(model);
}


TEST(ForEachRuleSuite, twoRoundsBasicRules)
{
    GameModel model;
    model.addVariable("Rounds", 2);
    
    std::vector<rules::IRule*> rules;
    rules.emplace_back(std::make_unique<GlobalMessage>("first"));
    rules.emplace_back(std::make_unique<GlobalMessage>("second"));
    rules.emplace_back(std::make_unique<GlobalMessage>("third"));
    ForEachRule foreach(rules);
    foreach.executeRule(model);
}

