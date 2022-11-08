#include "IRule.h"
#include <string>

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(std::string c);
        void executeRule(GameModel model) override;
        std::vector<std::string> getTokens(std::string str);
    private:
        std::string failCondition;
};