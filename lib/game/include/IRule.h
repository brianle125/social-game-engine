#pragma once

namespace rules {

	class IRule {
	public:
		virtual ~IRule() {}
		virtual void ExecuteRule() = 0;

	private:
	};
}