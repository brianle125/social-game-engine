#include <vector>
#include <string>

#include "IRule.h"

using namespace std;

class ForEachRule : public rules::IRule {
    public:
        ForEachRule(vector<string> list);
        ~ForEachRule() {}
        void ExecuteRule() override;

    private:
        //list object to operate on, modify later
        vector<string> ruleList;
};