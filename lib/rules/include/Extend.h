#include <vector>
#include "IRule.h"
#include <ContentVariant>

class Extend{
    public:
        Extend(std::vector<dataBucket>& originalVector,std::vector<dataBucket>& additionVector);

        void ExecuteRule();

    private:
        vector<dataBucket>& originalVector;
        vector<dataBucket>& additionVector;
};