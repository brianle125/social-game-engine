#include <ShuffleList.h>
#include <vector>
#include <optional>

ShuffleList::ShuffleList(std::string key)
: k(key) {}


std::optional<std::vector<rules::IRule>> ShuffleList::executeRule(GameModel model) 
{
    dataVariant v = model.getVariable(k);
    rva::visit(shuffleVisitor(), v);
    model.setVariable(k, v);
    return nullopt;
}