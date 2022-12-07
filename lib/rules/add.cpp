#include <add.h>

Add::Add(std::string key, dataVariant value) 
: key(key), val(value) {}

std::optional<std::vector<rules::IRule>> Add::executeRule(GameModel model) {
    dataVariant v = model.getVariable(key);
   // v = v + val;
    dataVariant result = rva::visit(addVisitor(), v, val);
    model.setVariable(key, result);
    return nullopt;
}