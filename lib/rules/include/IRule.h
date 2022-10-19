#pragma once
#include <string>

namespace rules {

	class IRule {
	public:
		IRule();
		IRule(std::string name) noexcept;
		
		virtual void ExecuteRule() = 0;
		virtual ~IRule() = 0;

	private:
		std::string ruleName;
	};
}