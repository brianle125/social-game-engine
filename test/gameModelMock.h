#include "GameModel.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using lookupKey = std::string;

namespace {
class MockGameModel : public GameModel {
public:
    MOCK_METHOD(void, addSetupVariable, (lookupKey key, dataVariant value));
    MOCK_METHOD(void, addConstant, (lookupKey key, dataVariant value));
    MOCK_METHOD(void, addVariable, (lookupKey key, dataVariant value));
    MOCK_METHOD(dataVariant, getVariable, (lookupKey key));
    MOCK_METHOD(void, setVariable, (lookupKey key, dataVariant value));
    MOCK_METHOD(void, addSetupVariablesFromJson, (json setup));
    MOCK_METHOD(void, addConstantsFromJson, (json constants));
    MOCK_METHOD(void, addVariablesFromJson, (json variables));
};
}