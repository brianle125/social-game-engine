#pragma once
#include <string>

#include <../../game/include/GameModel.h>

namespace rules {

	class IRule {
	public:
		virtual void executeRule(GameModel model) = 0;
		IRule();
		IRule(std::string name);
		
		virtual ~IRule();

	private:

		std::string ruleName;
	};
}