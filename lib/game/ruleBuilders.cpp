#include <memory>
#include <nlohmann/json.hpp>
#include "GameCreator.h"

#include "GlobalMessage.h"
#include "ForEachRule.h"
//#include "ShuffleList.h"


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


	// ruleBuilders.emplace("foreach", 
	// 	[](json ruleData) -> std::unique_ptr<rules::IRule> {
	// 		dataVariant list = ruleData["rules"];
	// 		auto newRule = std::make_unique<ForEachRule>(ForEachRule(ruleData["list"]));
	// 		return std::move(newRule);
	// });	

	// //tentative
	// ruleBuilders.emplace("when", 
	// 	[](json ruleData) -> std::unique_ptr<rules::IRule> {
	// 		auto whileCon = ruleData["while"];
	// 		auto untilCon = ruleData["until"];

	// 		if(whileCon)
	// 		{
	// 			auto newRule = std::make_unique<WhenRule>(WhenRule(ruleData["list"]));
	// 			return std::move(newRule); 
	// 		}
	// 		else if(untilCon) {
	// 			auto newRule = std::make_unique<WhenRule>(WhenRule(ruleData["list"]));
	// 			return std::move(newRule);
	// 		}
	// });	
	
	
}