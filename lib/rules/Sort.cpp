#include "include/sort.h"


Sort::Sort(std::string key) 
: key(key) {}

Sort::Sort(std::string key, std::string sortingKey)
: key(key), sortingKey(sortingKey) {}

optional<std::vector<rules::IRule>> executeRule(GameModel model) override {
    if (sortingKey.empty()) {
        rva::visit(sortVisitor, key);
    } else {
        rva::visit(sortVisitor, key, sortingKey);
    }
    return nullopt;
}

// Sort::Sort(std::vector<dataVariant>& vector):sortVector(vector){}


// void Sort::ExecuteRule()
// {
//     std::sort(sortVector.begin(),sortVector.end());
// }