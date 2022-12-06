#include "inputChoiceRule.h"

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

class MockInputChoiceRule : public InputChoiceRule {
public:
    MOCK_METHOD(void, getInput, (Player *target, std::string msg), (override));
};

class InputChoiceRuleTest : public ::testing::Test {
protected:
    InputChoiceRule rule;
    MockPlayer player{"name"};
    MockServer server;
    MockGameModel model;

    void SetUp() override {
        std::vector<dataVariant> choices{dataVariant(std::string("TEST"))};
        rule = InputChoiceRule(&player, "prompt", choices, "result", &server, 0);
    }
};

TEST_F(InputChoiceRuleTest, executeShouldCallGetInputWithInputs) {
    MockInputChoiceRule mockRule;
    mockRule.target = &player;
    mockRule.prompt = "prompt";
    EXPECT_CALL(mockRule, getInput(&player, "prompt: []\n"));

    mockRule.executeRule(model);
}

// TODO: figure out how to deal with static system_clock method
// TEST_F(InputChoiceRuleTest, getInputShouldCallSendAndAwait) {
//     networking::Message message = { rule.target->connection, "prompt" };
//     std::deque<networking::Message> messages = { message };

//     auto time = std::chrono::system_clock::now();
//     networking::Response response{ &rule, time };

//     EXPECT_CALL(std::chrono::system_clock, now()).WillOnce(testing::Return(time));

//     EXPECT_CALL(server, send(messages)).Times(1);
//     EXPECT_CALL(server, awaitResponse(rule.target->connection, response)).Times(1);

//     rule.getInput(&player, "prompt");
// }

TEST_F(InputChoiceRuleTest, receiveInputShouldReturnSuccessOnTimeout) {
    std::chrono::duration<double> duration = std::chrono::seconds(11);
    rule.timeout = 10;

    auto status = rule.receiveResponse("PEPW", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);
}

TEST_F(InputChoiceRuleTest, receiveInputShouldReturnSuccess) {
    std::chrono::duration<double> duration = std::chrono::seconds(11);

    auto status = rule.receiveResponse("TEST", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::success);
}

TEST_F(InputChoiceRuleTest, receiveInputShouldReturnFailureAndGetInput) {
    std::chrono::duration<double> duration = std::chrono::seconds(11);
    std::vector<dataVariant> choices = {dataVariant(std::string("NOTPEPW"))};
    MockInputChoiceRule mockRule;
    mockRule.target = &player;
    mockRule.choices = choices;
    mockRule.prompt = "prompt";

    EXPECT_CALL(mockRule, getInput(&player, "prompt: [NOTPEPW]\n")).Times(1);

    auto status = mockRule.receiveResponse("PEPW", duration);
    
    EXPECT_EQ(status, rules::InputRule::InputValidation::failure);
}
}
