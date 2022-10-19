#include <ParellelFor.h>
#include <algorithm>
#include <execution>

ParallelFor::ParallelFor(vector<string> & list) : memberList(list) {}

void ParallelFor::executeRule() {
    std::for_each(memberList.begin(), memberList.end(),
    [](auto&& member)
    {
        //To do: execute each member
    });
}