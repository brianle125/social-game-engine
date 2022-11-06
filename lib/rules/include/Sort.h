#include <vector>
#include "IRule.h"
#include <ContentVariant>


class Sort{
    public:
        Sort(std::vector<myVariant>& vector);
        void Sort::executeRule() override;

    private:
       std::vector<myVariant>& sortVector;
};