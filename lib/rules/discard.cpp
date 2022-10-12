#include "include/discard.h"
#include <iostream>

Discard::Discard(vector<string> newList, int disc)
{
    list = newList;
    discardAmt = disc;
}

vector<string> Discard::getList()
{
    return list;
}

void Discard::setList(vector<string> newList)
{
    list = newList;
}

// TODO: ask if discard from front or back or random
void Discard::discardBack()
{
    for (int i = 0; i < discardAmt; i++)
    {
        list.pop_back();
    }
}

// int main()
// {

//     vector<string> ok;
//     ok.push_back("hello");
//     ok.push_back("one");
//     ok.push_back("two");
//     ok.push_back("three");

//     Discard test(ok, 2);

//     test.discardBack();

//     for (auto i : test.getList())
//     {
//         cout << i << " ";
//     }
//     cout << endl;
// }