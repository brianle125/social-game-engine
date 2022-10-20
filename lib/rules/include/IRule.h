#pragma once
#include <string>

namespace rules {

	class IRule {
	public:
		virtual void executeRule() = 0;
		IRule();
		IRule(std::string name);
		
		virtual ~IRule();

	private:
		std::string ruleName;
	};
}