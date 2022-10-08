#pragma once
 

#include <../../include/IRule.h>
#include <../../include/Game.h>
#include <string>



namespace rules{

	class Add: public IRule
    {
        public:
            //add value parameter can be either integer literal or name of a variable or constant containing the value to add.
            Add(std::string to,gameModel::Game& game ,int addition_value);
            Add(std::string to,gameModel::Game& game ,std::string addition_source);
            ~Add();

            void ExecuteRule();

            void add();

		

	    private:
            std::string target;
            int value;
            gameModel::Game game;
	};
}