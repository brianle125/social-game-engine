#include <vector>
#include "IRule.h"
#include <string>

class Switch{
    
public:

    Switch(int a, std::vector <std::pair<int,std::string>> vector);
    void runRule();
    
private:

    int value;
    //When we get to compilation have to change int to generic and string to rule vector
    std::vector <std::pair<int,std::string>> myVector;
};
