#pragma once

#include <vector>
#include <memory>

#include "ContentVariant.h"


class GameModel {
public:
    void addConstant(std::string name, dataVariant value);
    void addVariable(std::string name, dataVariant value);
    dataVariant getVariable(std::string key);
    void setVariable(std::string key, dataVariant value);

private:
    
    //list of Players
    //dictionary of setup

    std::unordered_map<std::string, dataVariant> constants;
    std::unordered_map<std::string, dataVariant> variables;

};
