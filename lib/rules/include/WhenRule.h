#include "IRule.h"

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(bool con);
        void executeRule() override;
    private:
        bool condition;
};