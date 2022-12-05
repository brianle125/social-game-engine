#include "GameModel.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class MockGameModel : public GameModel {
public:
    MOCK_METHOD(void, addSetupVariable, (lookupKey key, dataVariant value), (override));
    MOCK_METHOD(void, addConstant, (lookupKey key, dataVariant value), (override));
    MOCK_METHOD(void, addVariable, (lookupKey key, dataVariant value), (override));
    MOCK_METHOD(dataVariant, getVariable, (lookupKey key), (override));
    MOCK_METHOD(void, setVariable, (lookupKey key, dataVariant value), (override));
    MOCK_METHOD(void, addSetupVariablesFromJson, (json setup), (override));
    MOCK_METHOD(void, addConstantsFromJson, (json constants), (override));
    MOCK_METHOD(void, addVariablesFromJson, (json variables), (override));
};
