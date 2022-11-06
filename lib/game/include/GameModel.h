#pragma once

#include <vector>
#include <memory>

#include "ContentVariant.h"


class GameModel {
public:
    void addConstant(std::string name, dataBucket value);
    dataBucket getConstant(std::string key);
    void addVariable(std::string name, dataBucket value);
    dataBucket getVariable(std::string key);
    //void setVariable(std::string key, //variant or raw value?//);

private:
    
    //list of Players
    //dictionary of setup

    std::unordered_map<std::string, dataBucket> constants;
    std::unordered_map<std::string, dataBucket> variables;

};