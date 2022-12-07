//#include "include/sort.h"
#include <Sort.h>
#include <vector>
#include <optional>

Sort::Sort(std::string key) 
: key(key) {}

Sort::Sort(std::string key, std::string sortingKey)
: key(key), sortingKey(sortingKey) {}

std::optional<std::vector<rules::IRule>> Sort::executeRule(GameModel model) {
    dataVariant v = model.getVariable(key);
    if (sortingKey.empty()) {
        rva::visit(sortVisitor(), v);
    } else {
        //rva::visit(sortVisitor(), v, sortingKey);
    }
    return nullopt;
}