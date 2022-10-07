#include "include/reverse.h"
#include <iostream>

using namespace std;

vector<string> Reverse::getList()
{
    return list;
}

void Reverse::setList(vector<string> newList)
{
    list = newList;
}

void Reverse::reverseList()
{
    reverse(list.begin(), list.end());
}

// int main()
// {
//     Reverse test;

//     vector<string> ok;
//     ok.push_back("hello");
//     ok.push_back("one");
//     ok.push_back("two");
//     ok.push_back("three");

//     test.setList(ok);
//     test.reverseList();

//     // printing the reversed list
//     for (auto i : test.getList())
//     {
//         cout << i << " ";
//     }
//     cout << endl;
// }