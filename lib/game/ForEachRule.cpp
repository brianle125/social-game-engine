#include "include/ForEachRule.h"
#include <vector>
#include <iostream>

using namespace std;

ForEachRule::ForEachRule(vector<string> list) : ruleList(list) {}

void ForEachRule::ExecuteRule() 
{
    for(auto rule: ruleList)
    {
        //execute rule; todo
        cout << "testing foreach" << endl;
    }
}

//testing only, removal later
int main()
{
    try 
    {
        vector<string> list = {"one", "two"};
        ForEachRule fe(list);
        fe.ExecuteRule();
    } 
    catch(exception &e)
    {
        cout << e.what() << endl;
        return -1;
    }
    
}