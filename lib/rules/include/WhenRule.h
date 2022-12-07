#include "IRule.h"
#include <string>

class WhenRule final : public rules::IRule
{
    public:
        WhenRule(std::vector<bool> cases, std::vector<std::vector<rules::IRule*>> list);
        std::optional<vector<rules::IRule>> executeRule(GameModel model) override;
    private:
        std::vector<bool> cases;
        std::vector<std::vector<rules::IRule*>> rulesCollection;
        
};