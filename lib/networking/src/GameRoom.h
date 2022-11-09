//
// Created by Yiwen Wang on 2022-10-23.
//

#ifndef HTTP_SERVER_CPP_GAMEROOM_H
#define HTTP_SERVER_CPP_GAMEROOM_H

#include "GameRoomId.h"
class GameRoom {
private:
    GameRoomId id;
    std::string game_name;
public:
    GameRoom(const GameRoomId &, std::string);
    GameRoomId get_game_room_id() const;
    std::string get_game_name() const;
    std::string serialized() const;

};


#endif //HTTP_SERVER_CPP_GAMEROOM_H
