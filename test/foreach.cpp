#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ForEachRule.h"
#include "GlobalMessage.h"
#include "gameModelMock.h"
#include "LoopRule.h"


/** 
 * This section of tests simulate game construction 
 * through Gamemodel directly rather than through
 * JSON game construction. 
 */
//Printing messages
TEST(ForEachRuleSuite, oneRoundBasicRules)
{   
    MockGameModel model;
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
    EXPECT_CALL(model, getVariable("Rounds"));

    foreach.executeRule(model);

    EXPECT_EQ(RuleStatus::FINISHED, foreach.getStatus());

}

TEST(ForEachRuleSuite, fiveRoundsBasicRules)
{
    MockGameModel model;
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
    EXPECT_CALL(model, getVariable("Rounds"));

    foreach.executeRule(model);
    
    EXPECT_EQ(RuleStatus::FINISHED, foreach.getStatus());
}

TEST(ForEachSuite, nestedForEach)
{
    MockGameModel model;
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
    EXPECT_CALL(model, getVariable("Rounds"));

    foreach.executeRule(model);

    EXPECT_EQ(RuleStatus::FINISHED, foreach.getStatus());
}

TEST(ForEachSuite, complexAndNestedRules)
{
    MockGameModel model;
    model.addVariable("Rounds", 2);
    model.addVariable("upfrom", 1);
    model.addVariable("condition", false);
    bool con = std::get<bool>(model.getVariable("condition"));

    std::vector<rules::IRule*> rules;
    GlobalMessage glob("first");
    GlobalMessage glob2("second");
    GlobalMessage glob3("third");
    rules.emplace_back(std::move(&glob));
    rules.emplace_back(std::move(&glob2));
    rules.emplace_back(std::move(&glob3));
    LoopRule loop(rules, con);
    LoopRule loopTwo(rules, con);
    rules.emplace_back(std::move(&loop));
    rules.emplace_back(std::move(&loopTwo));
    EXPECT_CALL(model, getVariable("Rounds"));
    
    ForEachRule foreach(rules);
    foreach.executeRule(model);
    EXPECT_EQ(RuleStatus::FINISHED, foreach.getStatus());
}