#include <InParallel.h>

InParallel::InParallel(std::vector<rules::IRule> &rules) : rules{rules} {}

optional<vector<rules::IRule>> InParallel::executeRule(GameModel model) {
    for (auto &rule : rules) {
        rule.execute(model);
    }
    //
    // model.update() SOMETHING LIKE THIS MAYBE
    // OR return rules --> vector of rules to be executed within one server update cycle.
}
    