#include "IRule.h"

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(bool con);
    private:
        bool condition;
};