    #include "switch.h"
    
    Switch::Switch(int a, std::vector <std::pair<int,std::string>> vector){
        value = a;
        myVector = vector;
    }
    
    void Switch::runRule(){
        for(int i = 0; i < myVector.size(); i++){
            if((myVector.at(i)).first == value){
                std::cout << myVector[i].second;
            }
        }
    }
