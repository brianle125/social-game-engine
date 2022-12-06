#include "inputTextRule.h"

#include "gameModelMock.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace {
class MockPlayer : public Player {
public:
    MockPlayer(string name) : Player(name) {}
};

class MockServer : public networking::Server {
public:
    MOCK_METHOD(void, send, (std::deque<networking::Message> messages));
    MOCK_METHOD(void, awaitResponse, (networking::Connection client, networking::Response response));
};

class MockInputTextRule : public InputTextRule {
public:
    MOCK_METHOD(void, getInput, (Player *target, std::string msg), (override));
};

class InputTextRuleTest : public ::testing::Test {
protected:
    InputTextRule rule;
    MockPlayer player{"name"};
    MockServer server;
    MockGameModel model;

    void SetUp() override {
        rule = InputTextRule(&player, "prompt", "result", &server, 0);
    }
};

TEST_F(InputTextRuleTest, executeShouldCallGetInputWithInputs) {
    MockInputTextRule mockRule;
    mockRule.target = &player;
    mockRule.prompt = "prompt";
    EXPECT_CALL(mockRule, getInput(&player, "prompt: "));

    mockRule.executeRule(model);
}

TEST_F(InputTextRuleTest, receiveInputShouldReturnSuccess) {
    std::chrono::duration<double> duration = std::chrono::seconds(11);

    auto status = rule.receiveResponse("TEST", duration);
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);

    rule.timeout = 10;
    status = rule.receiveResponse("TEST", duration);
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);
}
}
