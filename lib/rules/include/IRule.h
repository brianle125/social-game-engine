#pragma once
#include <string>

namespace rules {

	class IRule {
	public:
		virtual void executeRule() = 0;
		IRule();
		IRule(std::string name) noexcept;
		
		virtual ~IRule() = 0;

	private:

		std::string ruleName;
	};
}