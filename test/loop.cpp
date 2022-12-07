#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LoopRule.h"
#include "ForEachRule.h"
#include "GlobalMessage.h"


/** 
 * This section of tests simulate game construction 
 * through Gamemodel directly rather than through
 * JSON game construction. 
 */

//Check whether globalmessages can print within Loop
TEST(LoopRuleSuite, basicRuleLoop)
{
    GameModel model;
    model.addVariable("Rounds", 1);
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
    loop.executeRule(model);

    EXPECT_EQ(RuleStatus::FINISHED, loop.getStatus());

}


TEST(LoopRuleSuite, executeNestedLoopRules)
{
    GameModel model;
    model.addVariable("Rounds", 1);
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
    LoopRule nested(rules, con);
    rules.emplace_back(std::move(&nested));
    LoopRule loop(rules, con);
    loop.executeRule(model);

    EXPECT_EQ(RuleStatus::FINISHED, loop.getStatus());

}

TEST(LoopRuleSuite, executeNestedLoopAndForEachRules)
{
    GameModel model;
    model.addVariable("Rounds", 1);
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
    LoopRule nested(rules, con);
    rules.emplace_back(std::move(&nested));
    ForEachRule foreach(rules);
    rules.emplace_back(std::move(&foreach));

    LoopRule loop(rules, con);
    loop.executeRule(model);

    EXPECT_EQ(RuleStatus::FINISHED, loop.getStatus());

}