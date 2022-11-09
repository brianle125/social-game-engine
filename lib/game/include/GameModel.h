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
    void setVariable(std::string key, dataVariant value);
    void addConstantsFromJson(json constants);
    void addVariablesFromJson(json variables);
    

private:
    VariantParser parser;
    //list of Players
    //dictionary of setup

    std::unordered_map<std::string, dataVariant> constants;
    std::unordered_map<std::string, dataVariant> variables;

};
