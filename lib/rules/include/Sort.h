#include <vector>
#include "IRule.h"
#include <ContentVariant>


class Sort{
    public:
        Sort(std::vector<dataBucket>& vector);

        void Sort::ExecuteRule();

    private:
        vector<dataBucket>& sortVector;
};