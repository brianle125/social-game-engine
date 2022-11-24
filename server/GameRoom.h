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
#include "RoundNumber.h"
#include "GUITask.h"
#include "Message.h"
#include "PlayerInput.h"
#include "Id.h"
class GameRoom {
private:
    GameRoomId id;
    std::string game_name;
    std::optional<nlohmann::json> game_config;
    GameStatus game_status = GameStatus::not_started;
    std::vector<PlayerId> player_ids;
    std::vector<AudienceId> audience_ids;

    RoundNumber round_number;
    std::vector<GUITask> GUI_tasks;
    std::vector<Message> messages;
    std::vector<PlayerInput> player_inputs;

public:
    static std::optional<GameRoom> from_json(const nlohmann::json& j);
    GameRoom(const GameRoomId &, const std::string&);
    GameRoom(const GameRoomId &, const std::string&,
             const std::optional<nlohmann::json>&,
             GameStatus, const std::vector<PlayerId> &,
             const std::vector<AudienceId> &, const RoundNumber&,
             const std::vector<GUITask> &, const std::vector<Message> &,
             const std::vector<PlayerInput> &);
    GameRoom(GameRoomId &&, std::string&&);

    GameRoomId get_game_room_id() const;
    std::string get_game_name() const;
    std::optional<nlohmann::json> get_game_config() const;
    GameStatus get_game_status() const;
    std::vector<PlayerId> get_players() const;
    std::vector<AudienceId> get_audiences() const;
    RoundNumber get_round_number() const;
    std::vector<GUITask> get_GUI_tasks() const;
    std::vector<Message> get_messages() const;
    std::vector<PlayerInput> get_player_inputs() const;
    std::string serialized() const;
    bool operator== (const GameRoom &other) const;
    GameRoom with_config(const nlohmann::json&) const;
    GameRoom with_game_status(GameStatus) const;
    GameRoom with_player_id(const PlayerId player_id) const;
    GameRoom with_audience_id(const AudienceId audience_id) const;

    GameRoom with_round_number(const RoundNumber round_number) const;
    GameRoom with_GUI_task(const GUITask GUI_task) const;
    GameRoom with_message(const Message message) const;
    GameRoom with_player_input(const PlayerInput player_input) const;

    GameRoom delete_GUI_task(const Id GUI_task_id) const;
    GameRoom delete_message(const Id message_id) const;
};

#endif //HTTP_SERVER_CPP_GAMEROOM_H
