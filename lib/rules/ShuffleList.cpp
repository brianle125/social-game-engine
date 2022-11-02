#include "include/ShuffleList.h"
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

ShuffleList::ShuffleList(vector<string>& l)
: memberList(l) {}


//adapted from https://www.techiedelight.com/shuffle-vector-cpp/
void ShuffleList::executeRule(GameModel model) 
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count(); //change to better random generator later
    std::shuffle(memberList.begin(), memberList.end(), default_random_engine(seed));
}