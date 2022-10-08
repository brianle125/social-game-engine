#pragma once

namespace rules {

	class IRule {
	public:
		virtual void executeRule();

		~IRule();

	private:
	};
}