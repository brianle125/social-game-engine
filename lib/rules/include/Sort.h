#include <vector>
#include "IRule.h"
#include <ContentVariant>


class Sort{
    public:
        Sort(std::vector<dataVariant>& vector);

        void Sort::ExecuteRule();

    private:
        vector<dataVariant>& sortVector;
};