#include <vector>
#include "IRule.h"
#include <ContentVariant>

class Extend{
    public:
        Extend(std::vector<dataVariant>& originalVector,std::vector<dataVariant>& additionVector);

        void ExecuteRule();

    private:
        vector<dataVariant>& originalVector;
        vector<dataVariant>& additionVector;
};