#include <IRule.h>

using namespace std;

rules::IRule::IRule() {}

rules::IRule::IRule(std::string name)
	: ruleName(name) {}

	rules::IRule::~IRule() {}