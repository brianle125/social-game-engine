#include <vector>
#include <algorithm>
#include <string>
#include "IRule.h"

using namespace std;

class ShuffleList final : public IRule {
    private:
        vector<string>& memberList;
    
    public:
        ShuffleList(vector<string>& l);
        void ExecuteRule() override;

};