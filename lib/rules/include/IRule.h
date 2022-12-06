#pragma once
#include <string>
#include <optional>

#include <../../game/include/GameModel.h>

using namespace std;

enum RuleStatus {
	FINISHED,
	AWAITING_INPUT,
	INCOMPLETE
};

namespace rules {

	class IRule {
	public:
		virtual optional<vector<IRule>> executeRule(GameModel model) = 0;
		IRule();
		IRule(string name);
		
		virtual ~IRule();
		
		RuleStatus getStatus() { return status; }
		bool isParallel() { return parallel; } 
		int getParallelCount() { return parallelStackCount; }

	private:

		string ruleName;

	protected:
		RuleStatus status = FINISHED;
		bool parallel = false;
		int parallelStackCount = 1;
	};
}