#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ForEachRule.h"


TEST(ForEachTest, runRules)
{
    std::vector<rules::IRule> rules;
    rules.emplace_back(GlobalMessage{"one"});
    rules.emplace_back(GlobalMessage{"one"});
    rules.emplace_back(GlobalMessage{"one"});
    rules.emplace_back(GlobalMessage{"one"});
    ForEachRule foreach(rules);
    EXPECT_CALL(foreach, executeRule()).Times(1);
}



