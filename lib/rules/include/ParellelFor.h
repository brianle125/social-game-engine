#include "IRule.h"
#include <vector>


class ParallelFor final : public rules::IRule {
    public:
        ParallelFor(vector<std::string> & list);
        void executeRule(GameModel model) override;
    private:
        vector<std::string> memberList; 
};

