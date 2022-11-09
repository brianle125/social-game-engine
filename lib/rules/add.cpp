#include "include/ForEachRule.h"



rules::Add::Add(std::string to,gameModel::Game& game ,int addition_value)
{
    target = to;
    game = game;
    value = addition_value;



}



rules::Add::Add(std::string to,gameModel::Game& game ,std::string addition_source)
{
    target = to;
    game = game;
    
    // TODO once gamemodel variable implimentation is cemented add call to fetch value of named variable
}

void rules::Add::ExecuteRule(){
    add();
}

void rules::Add::add(){
    //TODO once gamemodel variable implimentation is cemented add call to modify value of named variable
}
