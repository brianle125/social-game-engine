#include "IRule.h"
#include <vector>

using namespace std;

class ParallelFor final : public rules::IRule {
    public:
        ParallelFor(vector<string> & list);
        void executeRule() override;
    private:
        vector<string> memberList; 
};

