#include <vector>
#include "IRule.h"
#include <string>
#pragma once

class Switch{
    
public:

    Switch(int a, std::vector <std::pair<int,std::string>> vector);
    ~Switch();
    void Switch::executeRule() override;
    
private:

    int value;
    //When we get to compilation have to change int to generic and string to rule vector
    std::vector <std::pair<int,std::string>> myVector;
};
