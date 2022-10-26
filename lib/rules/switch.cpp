    #include "switch.h"
    
    Switch::Switch(int a, std::vector <std::pair<int,std::string>> vector){
        value = a;
        myVector = vector;
    }

    Switch::~Switch(){}
    
    void Switch::runRule(){
        for(int i = 0; i < myVector.size(); i++){
            if((myVector.at(i)).first == value){
                std::cout << myVector[i].second;
            }
        }
    }

    //Text below was used for testing 
    // int x = 2;
    // std::pair<int,std::string> pair_1;
    // std::pair<int,std::string> pair_2;
    // std::pair<int,std::string> pair_3;
    // pair_1.first = 1;
    // pair_1.second = "String_1 ";
    // pair_2.first = 2;
    // pair_2.second = "String_2 ";
    // pair_3.first = 3;
    // pair_3.second = "String_3 ";
    // std::vector<std::pair<int,std::string>> cases = {pair_1,pair_2,pair_3};
    // Switch mySwitch = Switch{x,cases};
    // mySwitch.runRule();  
