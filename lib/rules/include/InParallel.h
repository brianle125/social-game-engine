#include "IRule.h"
#include <vector>
#include <algorithm>
#include <execution>

using namespace std;

class InParallel final : public rules::IRule {
    public:
        InParallel(vector<string> & list);
        void ExecuteRule() override;
    private:
        vector<string> memberList; 
};

