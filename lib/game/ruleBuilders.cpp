#include <memory>
#include <nlohmann/json.hpp>
#include "GameCreator.h"

#include "GlobalMessage.h"
#include "ShuffleList.h"


using json = nlohmann::json;

void GameCreator::GenerateRuleBuilders() {
	/*	RULE BUILDER TEMPLATE:
	ruleBuilders.emplace("rule-name", 
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			//whatever you need to create your rule here
			return std::move(newRule);
		});
	*/

/////////////////////////////// OUTPUT ////////////////////////////////

	ruleBuilders.emplace("global-message", 
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			auto newRule = std::make_unique<GlobalMessage>(GlobalMessage(ruleData["value"]));
			return std::move(newRule);
		});	

	
}