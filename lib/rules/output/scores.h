#include <iostream>
#include <vector>
#pragma once
//Player class included to test the function
// class Player{
//     public:

//     Player(std::string passedName, double passedScore);
//     ~Player();
//     std::string name;
//     int score;
// };

class Scores{
    public:
    Scores(std::vector<Player> passedPlayers);
    ~Scores();
    void outputScores();
    
    private:
    std::vector<Player> players;
};
