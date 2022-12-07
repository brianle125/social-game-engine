#include "include/reverse.h"


Reverse::Reverse(std::string key)
: k(key) {}

std::optional<std::vector<rules::IRule>> Reverse::executeRule(GameModel model) {
    dataVariant v = model.getVariable(k);
    rva::visit(reverseVisitor(), v);
    model.setVariable(k, v);
    return nullopt;
}

// vector<string> Reverse::getList()
// {
//     return list;
// }

// // TODO: remove set and use constructor instead?
// void Reverse::setList(vector<string> newList)
// {
//     list = newList;
// }

// void Reverse::reverseList()
// {
//     reverse(list.begin(), list.end());
// }
