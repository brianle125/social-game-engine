#include "include/ForEachRule.h"
#include <vector>
#include <iostream>


ForEachRule::ForEachRule(std::vector<string> & list) : memberList(list) {}

void ForEachRule::executeRule(GameModel model) 
{
    for(auto rule: memberList)
    {
        //execute rules in the json array; todo
    }
}

//testing only, removal later
// int main()
// {
//     try 
//     {
//         vector<string> list = {"one", "two"};
//         ForEachRule fe(list);
//         fe.executeRule();
//     } 
//     catch(exception &e)
//     {
//         cout << e.what() << endl;
//         return -1;
//     }  
// }