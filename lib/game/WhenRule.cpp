#include "include/WhenRule.h"
#include <vector>

using namespace std;

WhenRule::WhenRule(bool con) : condition(con) {}

void WhenRule::ExecuteRule() 
{
    if(condition)
    {
        //TODO: execute rule here
    }
}
