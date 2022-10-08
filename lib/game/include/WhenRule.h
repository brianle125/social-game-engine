#include "IRule.h"

class WhenRule final : public IRule
{
    public:
        WhenRule(bool con);
    private:
        bool condition;
};