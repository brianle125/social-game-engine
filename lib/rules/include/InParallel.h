#include "IRule.h"
#include <vector>

class InParallel final : public rules::IRule {
    public:
        InParallel(std::vector<IRule> &rules);
        void executeRule(GameModel model) override;
    private:
        std::vector<IRule> rules;
};

