#include "IRule.h"
#include <vector>
#include <algorithm>
#include <execution>

using namespace std;

class InParallel final : public rules::IRule {
    public:
        InParallel(vector<string> & list);
        void executeRule() override;
    private:
        vector<string> memberList; 
};

