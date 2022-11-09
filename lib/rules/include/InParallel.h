#include "include/IRule.h"
#include <vector>

class InParallel final : public rules::IRule {
    public:
        InParallel(std::vector<rules::IRule> &rules);
        optional<vector<rules::IRule>> executeRule(GameModel model) override;
    private:
        std::vector<IRule> rules;
};

