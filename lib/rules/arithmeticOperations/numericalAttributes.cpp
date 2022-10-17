#include "numericalAttributes.h"

class NumericalAttributes{
   
    public:
   
    NumericalAttributes(int passedCount, int passedFrom){
        count = passedCount + 1;
        from = passedFrom;
    }

    NumericalAttributes::~NumericalAttributes(){}
   
    void calculateNumericalAttributes(){
    std::vector<int> v(count);
    std::iota(v.begin(), v.end(), from);
    for(auto i:v){
        std::cout<<i<<std::endl;
        }
    }

    private:
    int count;
    int from;
};
