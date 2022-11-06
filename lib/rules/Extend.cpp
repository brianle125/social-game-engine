#include "include/Extend.h"


Extend::Extend(std::vector<dataVariant>& original,std::vector<dataVariant>& addition):originalVector(original),additionVector(addition){}


void Extend::ExecuteRule()
{
    originalVector.insert(originalVector.end(), additionVector.begin(), additionVector.end());
}