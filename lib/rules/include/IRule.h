#pragma once
#include <string>
#include <optional>

#include <../../game/include/GameModel.h>

using namespace std;

namespace rules {

	class IRule {
	public:
		virtual optional<vector<IRule>> executeRule(GameModel model) = 0;
		IRule();
		IRule(string name);
		
		virtual ~IRule();

	private:

		string ruleName;
	};
}