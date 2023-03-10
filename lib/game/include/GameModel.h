#pragma once

#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "ContentVariant.h"
#include "VariantParser.h"

using LookupKey = std::string;

class GameModel {
public:
    GameModel();
    void addConstant(std::string name, dataVariant value);
    void addVariable(std::string name, dataVariant value);
    dataVariant getVariable(LookupKey key);
    std::string fillInVariables(std::string_view toParse);
    void setVariable(std::string key, dataVariant value);
    void addSetupVariablesFromJson(json setup);
    void addConstantsFromJson(json constants);
    void addVariablesFromJson(json variables);
    

private:
    VariantParser parser;
    //list of Players
    //dictionary of setup

    dataVariant resolveKey(dataVariant currentVariable, std::vector<string_view> accessors, std::vector<string_view>::iterator& index);
    dataVariant lookupVariable(LookupKey key);
    std::unordered_map<std::string, dataVariant> setup;
    std::unordered_map<std::string, dataVariant> constants;
    std::unordered_map<std::string, dataVariant> variables;

    void addSetupVariable(std::string name, dataVariant value);
};
