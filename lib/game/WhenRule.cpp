using namespace std;
#include "include/IRule.h"
#include <vector>

class WhenRule final : public IRule
{
    public:
        rules::WhenRule(bool con) : condition(con) {}
        void rules::executeRule() override
        {
            if(condition)
            {
                //TODO: execute rule here
            }
        }
    private:
        bool condition;
};