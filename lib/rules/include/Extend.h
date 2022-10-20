#include <vector>
#include "IRule.h"
#include <ContentVariant>

class Extend{
    public:
        Extend(std::vector<myVariant>& originalVector,std::vector<myVariant>& additionVector);

        void ExecuteRule();

    private:
        vector<myVariant>& originalVector;
        vector<myVariant>& additionVector;
};