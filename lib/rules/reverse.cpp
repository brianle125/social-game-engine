#include <reverse.h>


Reverse::Reverse(std::string key)
: k(key) {}

std::optional<std::vector<rules::IRule>> Reverse::executeRule(GameModel model) {
    dataVariant v = model.getVariable(k);
    rva::visit(reverseVisitor(), v);
    model.setVariable(k, v);
    return nullopt;
}