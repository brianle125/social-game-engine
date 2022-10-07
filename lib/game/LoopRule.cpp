using namespace std;

class LoopRule: public IRule
{
    public:
        void executeRule() override
        {
            int idx = 0;
            while(!failCondition)
            {
                //execute rules in the ruleList 
                //ruleList[idx];
                idx++;
            }
        }
    private:
        vector ruleList;
        bool failCondition;
};