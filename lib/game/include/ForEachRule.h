#include "IRule.h"
#include <vector>
#include <string>

using namespace std;

class ForEachRule final : public IRule
{
    public:
        ForEachRule(vector<string> & list);
        void ExecuteRule() override;

    private:
        //list object to operate on, modify later
        vector<string> & ruleList;
}