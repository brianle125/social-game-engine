#include "include/Extend.h"


Extend::Extend(std::vector<dataBucket>& original,std::vector<dataBucket>& addition):originalVector(original),additionVector(addition){}


void Extend::ExecuteRule()
{
    originalVector.insert(originalVector.end(), additionVector.begin(), additionVector.end());
}