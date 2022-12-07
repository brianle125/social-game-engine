#include <Deal.h>
#include <string>


Deal::Deal(std::string from, std::string to, int count)
: from_key(from), to_key(to), count(count) {}

std::optional<std::vector<rules::IRule>> Deal::executeRule(GameModel model) {
    dataVariant f = model.getVariable(from_key);
    dataVariant t = model.getVariable(to_key);
    //rva::visit(dealVisitor(), &f, &t, count);
    model.setVariable(from_key, f);
    model.setVariable(to_key, t);
    return nullopt;
}