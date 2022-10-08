using namespace std;
#include "IRule.h"
#include <vector>

class WhenRule final : public IRule
{
    public:
        WhenRule(bool con) : condition(con) {}
        void executeRule() override
        {
            if(condition)
            {
                //execute rule here
            }
        }
    private:
        bool condition;
};