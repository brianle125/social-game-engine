
#include <string>
//class game
using namespace std;
class CoinRule{
private:
    string ruleName;
    string list;
    string from;
    string to;
    int count;
    string value;

public:
    void setRuleName(string name);
    string getRuleName();
    void setlist(string list);
    string getList();
    void setFrom(string from);
    string getFrom();
    void setTo(string to);
    string getTo();
    void setCount(int count);
    int getCount();
    void setValue(string value);
    string getValue();

};