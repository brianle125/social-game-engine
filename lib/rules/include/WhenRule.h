#include "include/IRule.h"

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(std::string c);
        WhenRule(bool con);
        void executeRule(GameModel model) override;
    private:
        bool condition;
        std::string failCondition;
};