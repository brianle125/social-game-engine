//
// Created by Yiwen Wang on 2022-10-23.
//

#include "GameRoom.h"

// For nlohmann json serialization:
// https://stackoverflow.com/questions/38336046/how-to-use-json-c-with-my-own-object
void to_json(nlohmann::json& j, const GameRoom& g) {
    auto game_config = g.get_game_config();
    j = nlohmann::json{
            {"id", g.get_game_room_id().get_value()},
            {"gameName", g.get_game_name()},
            {"gameConfig", game_config ? *game_config : nlohmann::json()},
            {"gameStatus", g.get_game_status().get_value()}};
}

GameRoom::GameRoom(const GameRoomId &id, const std::string & game)
        : id(id), game_name(game){
}

GameRoom::GameRoom(GameRoomId &&id, std::string && game)
        : id(id), game_name(game){
}

GameRoom::GameRoom(
        const GameRoomId &id,
        const std::string&game,
        const std::optional<nlohmann::json>& config,
        GameStatus status)
        : id(id), game_name(game) {
    game_config = config;
    game_status = status;
}

GameRoomId GameRoom::get_game_room_id() const {
    return id;
}

std::string GameRoom::get_game_name() const {
    return game_name;
}

std::optional<nlohmann::json> GameRoom::get_game_config() const {
    return game_config;
}

GameStatus GameRoom::get_game_status() const {
    return game_status;
}

std::string GameRoom::serialized() const {
    nlohmann::json j = *this;
    return j.dump();
}
bool GameRoom::operator== (const GameRoom &other) const {
    return other.id == this->id;
}

GameRoom GameRoom::with_config(const nlohmann::json& config){
    GameRoom new_room(this->id, this->game_name, config, this->game_status);
    return new_room;
}

GameRoom GameRoom::with_game_status(GameStatus status) {
    GameRoom new_room(this->id, this->game_name, this->game_config, status);
    return new_room;
}