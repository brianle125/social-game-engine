#include "include/Extend.h"
#include <iostream>

Extend::Extend(stdvector<myVariant>& original,stdvector<myVariant>& addition):originalVector(original),additionVector(addition){}


void Extend::ExecuteRule()
{
    originalVector.insert(originalVector.end(), additionVector.begin(), additionVector.end());
}