#include "inputTextRule.h"

#include "gameModelMock.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace {
class MockPlayer : public Player {};

class MockServer : public networking::Server {
public:
    MOCK_METHOD(void, send, (std::deque<networking::Message> messages), (override));
    MOCK_METHOD(void, awaitResponse, (networking::Connection client, networking::Response response), (override));
};

class MockInputTextRule : public InputTextRule {
public:
    MOCK_METHOD(void, getInput, (Player *target, std::string msg), (override));
};

class InputTextRuleTest : public ::testing::Test {
protected:
    InputTextRule rule;
    MockPlayer player;
    MockServer server;
    MockGameModel model;

    void SetUp() override {
        rule = InputTextRule(&player, "prompt", "result", &server, 0);
    }
};

TEST(InputTextRuleTest, executeShouldCallGetInputWithInputs) {
    MockInputTextRule mockRule;
    EXPECT_CALL(mockRule, getInput(&player, "prompt: ")).Times(1);

    mockRule.execute(model);
}

TEST(InputTextRuleTest, getInputShouldCallSendAndAwait) {
    networking::Message message = { target->connection, "prompt" };
    std::deque<Message> messages = { message };

    auto time = std::chrono::system_clock::now();
    networking::Response response{ &rule, time };

    EXPECT_CALL(std::chrono::system_clock, now()).WillOnce(testing::Return(time));

    EXPECT_CALL(server, send(messages)).Times(1);
    EXPECT_CALL(server, awaitResponse(target->connection, response)).Times(1);

    rule.getInput(&player, "prompt");
}

TEST(InputChoiceRuleTest, receiveInputShouldReturnSuccess) {
    auto status = rule.receiveResponse("PEPW", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);
}
}
