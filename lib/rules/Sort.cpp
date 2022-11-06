#include "include/sort.h"


Sort::Sort(std::vector<dataBucket>& vector):sortVector(vector){}


void Sort::ExecuteRule()
{
    std::sort(sortVector.begin(),sortVector.end());
}