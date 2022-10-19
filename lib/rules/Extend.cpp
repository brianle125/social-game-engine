#include "include/Extend.h"


Extend::Extend(std::vector<myVariant>& original,std::vector<myVariant>& addition):originalVector(original),additionVector(addition){}


void Extend::ExecuteRule()
{
    originalVector.insert(originalVector.end(), additionVector.begin(), additionVector.end());
}