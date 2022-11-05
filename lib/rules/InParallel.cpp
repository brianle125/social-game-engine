#include <InParallel.h>

InParallel::InParallel(std::vector<IRule> &rules) : rules{rules} {}

void InParallel::executeRule(GameModel model) {
    for (auto &rule : rules) {
        rule.execute(model);
    }
    // 
    // model.update() SOMETHING LIKE THIS MAYBE
}
    