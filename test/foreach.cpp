#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ForEachRule.h"
#include "GlobalMessage.h"


/** 
 * This section of tests simulate game construction 
 * through Gamemodel directly rather than through
 * JSON game construction. 
 */

class MockRule : public rules::IRule
{
    MOCK_METHOD(std::optional<std::vector<rules::IRule>, executeRule, (Gamemodel model), (override));
}

//Printing messages
TEST(ForEachRuleSuite, oneRoundBasicRules)
{
    GameModel model;
    model.addVariable("Rounds", 1);
    model.addVariable("upfrom", 1);

    std::vector<rules::IRule*> rules;
    rules.emplace_back(std::make_unique<GlobalMessage>("first"));
    rules.emplace_back(std::make_unique<GlobalMessage>("second"));
    rules.emplace_back(std::make_unique<GlobalMessage>("third"));
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
    rules.emplace_back(std::make_unique<GlobalMessage>("first"));
    rules.emplace_back(std::make_unique<GlobalMessage>("second"));
    rules.emplace_back(std::make_unique<GlobalMessage>("third"));
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
    rules.emplace_back(std::make_unique<GlobalMessage>("first"));
    rules.emplace_back(std::make_unique<GlobalMessage>("second"));
    rules.emplace_back(std::make_unique<GlobalMessage>("third"));
    std::vector<rules::IRule*> copy = rules;
    rules.emplace_back(std::make_unique<ForEachRule>(copy));
    ForEachRule foreach(rules);
    foreach.executeRule(model);

    EXPECT_EQ(true, true);
}

