#pragma once

#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "ContentVariant.h"
#include "VariantParser.h"


class GameModel {
public:
    GameModel();
    void addConstant(std::string name, dataVariant value);
    void addVariable(std::string name, dataVariant value);
    dataVariant getVariable(std::string key);
    std::string fillInVariables(std::string_view toParse);
    void setVariable(std::string key, dataVariant value);
    void addSetupVariablesFromJson(json setup);
    void addConstantsFromJson(json constants);
    void addVariablesFromJson(json variables);
    

private:
    VariantParser parser;
    //list of Players
    //dictionary of setup

    std::unordered_map<std::string, dataVariant> setup;
    std::unordered_map<std::string, dataVariant> constants;
    std::unordered_map<std::string, dataVariant> variables;

    void addSetupVariable(std::string name, dataVariant value);
};
