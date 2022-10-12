#pragma once
#include <string>

namespace rules {

	class IRule {
	public:
		virtual void ExecuteRule() = 0;

		IRule(std::string name) noexcept;
		
		virtual ~IRule() = 0;

	private:

		std::string ruleName;
	};
}