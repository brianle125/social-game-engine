#include <vector>
#include <string>

#include "IRule.h"

using namespace std;

class ForEachRule final : public rules::IRule {
    public:
        ForEachRule(vector<string> & list);
        ~ForEachRule() {}
        void executeRule() override;

    private:
        //list object to operate on, modify later
        vector<string> memberList;
};