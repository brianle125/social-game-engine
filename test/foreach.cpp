#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ForEachRule.h"
#include "GlobalMessage.h"


/** 
 * This section of tests simulate game construction 
 * through Gamemodel directly rather than through
 * JSON game construction. 
 */


//Printing messages
TEST(ForEachRuleSuite, oneRoundBasicRules)
{
    GameModel model;
    model.addVariable("Rounds", 1);
    model.addVariable("upfrom", 1);

    std::vector<rules::IRule*> rules;
    GlobalMessage glob("first");
    GlobalMessage glob2("second");
    GlobalMessage glob3("third");
    rules.emplace_back(std::move(&glob));
    rules.emplace_back(std::move(&glob2));
    rules.emplace_back(std::move(&glob3));
    ForEachRule foreach(rules);
    foreach.executeRule(model);

    EXPECT_EQ(true, true);

}


TEST(ForEachRuleSuite, fiveRoundsBasicRules)
{
    GameModel model;
    model.addVariable("Rounds", 5);
    model.addVariable("upfrom", 1);
    
    std::vector<rules::IRule*> rules;
    GlobalMessage glob("first");
    GlobalMessage glob2("second");
    GlobalMessage glob3("third");
    rules.emplace_back(std::move(&glob));
    rules.emplace_back(std::move(&glob2));
    rules.emplace_back(std::move(&glob3));
    ForEachRule foreach(rules);
    foreach.executeRule(model);
    
    EXPECT_EQ(true, true);
}

TEST(ForEachSuite, nestedForEach)
{
    GameModel model;
    model.addVariable("Rounds", 2);
    model.addVariable("upfrom", 1);
    
    std::vector<rules::IRule*> rules;
    GlobalMessage glob("first");
    GlobalMessage glob2("second");
    GlobalMessage glob3("third");
    rules.emplace_back(std::move(&glob));
    rules.emplace_back(std::move(&glob2));
    rules.emplace_back(std::move(&glob3));
    ForEachRule nested(rules);
    rules.emplace_back(std::move(&nested));
    ForEachRule foreach(rules);
    foreach.executeRule(model);

    EXPECT_EQ(true, true);
}

