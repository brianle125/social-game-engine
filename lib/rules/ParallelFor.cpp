#include <ParallelFor.h>

ParallelFor::ParallelFor(std::vector<dataVariant> *elements, std::vector<IRule> &rules) : elements{elements}, rules{rules} {}

void ParallelFor::executeRule(GameModel model) {
    for (auto &rule : rules) {
        for (auto &object : *elements) {
            // TODO: ACTUALLY FIGURE OUT IMPLEMENTATION
            // MAYBE SOMETHING LIKE THIS help
            // auto target = rva::visit(someVisitor{}, object);
            // rule.setTarget(target);
            rule.execute(model);
        }
    }
}