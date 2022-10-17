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

    //Text below was used for testing 
    // int x = 2;
    // std::pair<int,std::string> pair1;
    // std::pair<int,std::string> pair2;
    // std::pair<int,std::string> pair3;
    // pair1.first = 1;
    // pair1.second = "jeein1";
    // pair2.first = 2;
    // pair2.second = "jeein2";
    // pair3.first = 3;
    // pair3.second = "jeein3";
    // std::vector<std::pair<int,std::string>> cases = {pair1,pair2,pair3};
    // Switch mySwitch = Switch{x,cases};
    // mySwitch.runRule();  
};
