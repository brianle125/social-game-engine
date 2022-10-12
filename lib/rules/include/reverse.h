#include <vector>
#include <algorithm>
#include <string>

using namespace std;
class Reverse

{
private:
    vector<string> list;

public:
    vector<string> getList();
    void setList(vector<string> newList);
    void reverseList();
};