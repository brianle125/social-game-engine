#include "IRule.h"
#include <vector>

class ParallelFor final : public rules::IRule {
    public:
        ParallelFor(std::vector<dataVariant> *elements, std::vector<rules::IRule> &rules);
        optional<vector<rules::IRule>> executeRule(GameModel model) override;
    private:
        std::vector<dataVariant> *elements;
        std::vector<IRule> rules;
};

