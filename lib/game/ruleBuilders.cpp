#include <memory>
#include <nlohmann/json.hpp>
#include "GameCreator.h"

#include "GlobalMessage.h"
#include "ForEachRule.h"
#include "WhenRule.h"
#include "LoopRule.h"
#include "ShuffleList.h"
#include "Sort.h"
#include "reverse.h"
#include "Deal.h"


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

	ruleBuilders.emplace("foreach", 
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			nlohmann::json rules = ruleData["foreach"]["rules"];
			std::vector<rules::IRule*> ruleList;

			//todo: construct the list of rules from the rules array
			// for(auto & rule : rules)
			// {
			// 	// ruleList.emplace_back(std::make_unique<>);
			// }
			auto newRule = std::make_unique<ForEachRule>(ForEachRule(ruleList));
			return std::move(newRule);
	});	

	ruleBuilders.emplace("when", 
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			auto cases = ruleData["when"]["cases"];
			std::vector<bool> conditions;
			std::vector<std::vector<rules::IRule*>> rulesCollection;
			for(unsigned int i = 0; i < cases.size(); i++)
			{	
				auto rules = ruleData["when"]["cases"][i]["rules"];
				//for each case, add each condition and construct its respective list of rules
				conditions.emplace_back(cases[i]["condition"]);
				for(auto rule : rules)
				{
					//construct rule
				}	
			}

			auto newRule = std::make_unique<WhenRule>(WhenRule(conditions, rulesCollection));
			return std::move(newRule);
	});	

	ruleBuilders.emplace("loop",
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			auto rulesToExecute = ruleData["loop"];
			std::vector<rules::IRule*> ruleList;
			json untilKeyword = ruleData["loop"]["until"];
			json whileKeyWord = ruleData["loop"]["while"];

			//needs to parse the keywords into a suitable boolean
			
			//or have loop refactored
			bool condition = true;

			if(!untilKeyword.is_null())
			{
				auto newRule = std::make_unique<LoopRule>(LoopRule(ruleList, condition));
				return std::move(newRule);
			}
			auto newRule = std::make_unique<LoopRule>(LoopRule(ruleList, condition));
			return std::move(newRule);
		}
	);

	ruleBuilders.emplace("shuffle",
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			auto newRule = std::make_unique<ShuffleList>(ShuffleList(ruleData["list"]));
			return std::move(newRule);
		}
	);

	ruleBuilders.emplace("sort", 
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			std::unique_ptr<Sort> newRule;
			if (ruleData["key"]) {
				newRule = std::make_unique<Sort>(Sort(ruleData["list"], ruleData["key"]));
			} else {
				newRule = std::make_unique<Sort>(Sort(ruleData["list"]));
			}
			return std::move(newRule);
	});	
	
	ruleBuilders.emplace("reverse",
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			auto newRule = std::make_unique<Reverse>(Reverse(ruleData["list"]));
			return std::move(newRule);
		}
	);
		
	ruleBuilders.emplace("deal",
		[](json ruleData) -> std::unique_ptr<rules::IRule> {
			auto newRule = std::make_unique<Deal>(Deal(ruleData["from"], ruleData["to"], ruleData["count"]));
			return std::move(newRule);
		}
	);
}