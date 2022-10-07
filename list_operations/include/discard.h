#include <vector>
#include <string>

using namespace std;

class Discard
{
private:
    vector<string> list;
    int discardAmt;

public:
    Discard(vector<string> newList, int disc);
    vector<string> getList();
    void setList(vector<string> newList);
    void discardBack();
};