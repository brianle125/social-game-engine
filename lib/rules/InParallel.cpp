#include <InParallel.h>
#include <algorithm>
#include <execution>

InParallel::InParallel(vector<string> & list) : memberList(list) {}

void InParallel::ExecuteRule() {
    std::for_each(std::execution::par, memberList.begin(), memberList.end(),
    [](auto&& member)
    {
        //To do: execute each member
    });
}