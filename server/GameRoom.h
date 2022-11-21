//
// Created by Yiwen Wang on 2022-10-23.
//

#ifndef HTTP_SERVER_CPP_GAMEROOM_H
#define HTTP_SERVER_CPP_GAMEROOM_H

#include <optional>
#include <nlohmann/json.hpp>
#include "GameRoomId.h"
#include "GameStatus.h"
#include "PlayerId.h"
#include "AudienceId.h"

class GameRoom {
private:
    GameRoomId id;
    std::string game_name;
    std::optional<nlohmann::json> game_config;
    GameStatus game_status = GameStatus::not_started;
    std::vector<PlayerId> player_ids;
    std::vector<AudienceId> audience_ids;

public:
    static std::optional<GameRoom> from_json(const nlohmann::json& j);
    GameRoom(const GameRoomId &, const std::string&);
    GameRoom(const GameRoomId &, const std::string&,
             const std::optional<nlohmann::json>&,
                     GameStatus, const std::vector<PlayerId> &,
                             const std::vector<AudienceId> &);
    GameRoom(GameRoomId &&, std::string&&);

    GameRoomId get_game_room_id() const;
    std::string get_game_name() const;
    std::optional<nlohmann::json> get_game_config() const;
    GameStatus get_game_status() const;
    std::vector<PlayerId> get_players() const;
    std::vector<AudienceId> get_audiences() const;
    std::string serialized() const;
    bool operator== (const GameRoom &other) const;
    GameRoom with_config(const nlohmann::json&) const;
    GameRoom with_game_status(GameStatus) const;
    GameRoom with_player_id(const PlayerId player_id) const;
    GameRoom with_audience_id(const AudienceId audience_id) const;
};

#endif //HTTP_SERVER_CPP_GAMEROOM_H
