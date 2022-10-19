#include <vector>
#include "IRule.h"
#include <ContentVariant>


class Sort{
    public:
        Sort(std::vector<myVariant>& vector);

        void Sort::ExecuteRule();

    private:
        vector<myVariant>& sortVector;
};