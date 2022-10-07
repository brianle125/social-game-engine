#include <vector>
#include <algorithm>

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