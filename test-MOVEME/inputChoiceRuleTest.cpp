#include "inputChoiceRule.h"

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

class MockInputChoiceRule : public InputChoiceRule {
public:
    MOCK_METHOD(void, getInput, (), (override));
};

class InputChoiceRuleTest : public ::testing::Test {
protected:
    InputChoiceRule rule;
    MockPlayer player;
    MockServer server;
    MockGameModel model;

    void SetUp() override {
        std::vector<dataVariant> choices = [];
        rule = InputChoiceRule(&player, "prompt", choices, "result", &server, 0);
    }
};

TEST(InputChoiceRuleTest, executeShouldCallGetInputWithInputs) {
    MockInputChoiceRule mockRule;
    EXPECT_CALL(mockRule, getInput(&player, "prompt:\n")).Times(1);

    mockRule.execute(model);
}

TEST(InputChoiceRuleTest, getInputShouldCallSendAndAwait) {
    networking::Message message = { target->connection, "prompt" };
    std::deque<Message> messages = { message };

    auto time = std::chrono::system_clock::now();
    networking::Response response{ &rule, time };

    EXPECT_CALL(std::chrono::system_clock, now()).WillOnce(testing::Return(time));

    EXPECT_CALL(server, send(messages)).Times(1);
    EXPECT_CALL(server, awaitResponse(target->connection, response)).Times(1);

    rule.getInput(&player, "prompt");
}

TEST(InputChoiceRuleTest, receiveInputShouldReturnSuccessOnTimeout) {
    std::chrono::duration<double> duration = std::chrono::seconds(11);
    rule.timeout = 10;

    auto status = rule.receiveResponse("PEPW", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);
}

TEST(InputChoiceRuleTest, receiveInputShouldReturnSuccess) {
    std::vector<dataVariant> choices = [dataVariant("PEPW")];

    auto status = rule.receiveResponse("PEPW", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);
}

TEST(InputChoiceRuleTest, receiveInputShouldReturnFailureAndGetInput) {
    std::vector<dataVariant> choices = [dataVariant("NOTPEPW")];
    MockInputChoiceRule mockRule;
    mockRule.choices = choices;

    EXPECT_CALL(mockRule, getInput(&player, "prompt: NOTPEPW\n")).Times(1);

    auto status = mockRule.receiveResponse("PEPW", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::failure);
}
}