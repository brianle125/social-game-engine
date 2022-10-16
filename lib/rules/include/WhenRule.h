#include "IRule.h"

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(bool con);
        void ExecuteRule() override;
    private:
        bool condition;
};