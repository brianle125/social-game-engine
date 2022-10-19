#include "include/WhenRule.h"
#include <vector>

using namespace std;

WhenRule::WhenRule(bool con) : condition(con) {}

void WhenRule::executeRule() 
{
    if(condition)
    {
        //TODO: execute rule here
    }
}
