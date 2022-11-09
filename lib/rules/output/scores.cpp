  #include "scores.h"
  #include "Player.h"
//Player class included to test the function
    
//     Player::Player(std::string passedName, double passedScore){
//         name = passedName;
//         score = passedScore;
//     }

//     Player::~Player(){}

//Need to change the player test vector to actual player vector once player class is written
   Scores::Scores(std::vector<Player> passedPlayers)
    {
        players = passedPlayers;
    }

    Scores::~Scores(){}
    
    void Scores::outputScores(){
    int current_min = players[0].score;
    int player_to_remove;
    int x = players.size();
    for(int i =0 ; i< x; i++)
    {
    for(int j= 0; j <x - i; j++)
    {
        if(current_min<=players[j].score)
        {
            current_min=players[j].score;
            player_to_remove=j;
        }
    }
    std::cout << players[player_to_remove].name << players[player_to_remove].score << std::endl;
    players.erase(players.begin() + player_to_remove);
    current_min = players[0].score;
    }
}
