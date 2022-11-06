//
// Created by Yiwen Wang on 2022-10-23.
//

#ifndef HTTP_SERVER_CPP_GAMEROOM_H
#define HTTP_SERVER_CPP_GAMEROOM_H

#include <optional>
#include <nlohmann/json.hpp>
#include "GameRoomId.h"

class GameRoom {
private:
    GameRoomId id;
    std::string game_name;
    std::optional<nlohmann::json> game_config;

public:
    GameRoom(const GameRoomId &, const std::string&);
    GameRoom(GameRoomId &&, std::string&&);
    GameRoomId get_game_room_id() const;
    std::string get_game_name() const;
    std::optional<nlohmann::json> get_game_config() const;
    std::string serialized() const;
    bool operator== (const GameRoom &other) const;
};

#endif //HTTP_SERVER_CPP_GAMEROOM_H
