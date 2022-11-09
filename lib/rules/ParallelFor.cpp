#include <ParallelFor.h>

ParallelFor::ParallelFor(std::vector<dataVariant> *elements, std::vector<rules::IRule> &rules) : elements{elements}, rules{rules} {}

optional<vector<rules::IRule>> ParallelFor::executeRule(GameModel model) {
    for (auto &rule : rules) {
        for (auto &object : *elements) {
            // TODO: ACTUALLY FIGURE OUT IMPLEMENTATION
            // MAYBE SOMETHING LIKE THIS help
            // auto target = rva::visit(someVisitor{}, object);
            // rule.setTarget(target);
            rule.execute(model);
        }
    }
    //***** or THIS implementation *****//
    // vector<rules::IRule> parallelRules;
    // auto currentRule = rules.erase(rules.begin()); // one rule per call of executeRule() ???

    // for (auto object : *elements) {
    //     auto target = rva::visit(someVisitor{}, object);
    //     currentRule.setTarget(target); // MAKE A COPY?
    //     parallelRules.push_back(currentRule);
    // }
    // return parallelRules; // vector of the same rule with different targets to be executed in the same server cycle
}