using namespace std;

class ForEachRule final : public IRule
{
    public:
        void executeRule() override
        {
            for(auto rule: ruleList)
            {
                //execute some rule
            }
        }

    private:
        //list object to operate on
        vector ruleList;
}