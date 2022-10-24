//
// Created by Yiwen Wang on 2022-10-23.
//

#include "GameRoom.h"
#include <format>
GameRoom::GameRoom(const GameRoomId &id, std::string game)
    : id(id), game_name(game){
}

GameRoomId GameRoom::get_game_room_id() const {
    return id;
}

std::string GameRoom::get_game_name() const {
    return game_name;
}

std::string GameRoom::serialized() const {
    std::string starter = "{\"gameRoomId\":\"";
    return starter + id.get_value() + "\",\"gameName\":\"" + game_name + "\"}";
}