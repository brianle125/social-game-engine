//
// Created by Yiwen Wang on 2022-10-23.
//

#include "GameRoom.h"
#include <stdexcept>

// For nlohmann json serialization:
// https://stackoverflow.com/questions/38336046/how-to-use-json-c-with-my-own-object
void to_json(nlohmann::json& j, const GameRoom& g) {
    auto game_config = g.get_game_config();
    std::vector<std::string> player_id_strings;
    for (const auto PlayerId: g.get_players()) {
        player_id_strings.push_back(PlayerId.get_value());
    }

    std::vector<std::string> audience_id_strings;
    for (const auto AudienceId: g.get_audiences()) {
        audience_id_strings.push_back(AudienceId.get_value());
    }

    j = nlohmann::json{
            {"id", g.get_game_room_id().get_value()},
            {"gameName", g.get_game_name()},
            {"gameConfig", game_config ? *game_config : nlohmann::json()},
            {"gameStatus", g.get_game_status().get_value()},
            {"playerIds", player_id_strings},
            {"audienceIds", audience_id_strings}
    };
}

std::optional <GameRoom> GameRoom::from_json(const nlohmann::json &j) {
    std::string gameStatusString = j.at("gameStatus").get<std::string>();
    std::optional<GameStatus> maybeGameStatus = GameStatus::try_parse(gameStatusString);
    if (!maybeGameStatus){
        throw std::invalid_argument("invalid gameStatus: " + gameStatusString);
    }
    GameRoomId id(j.at("id").get<std::string>());

    std::vector<std::string> player_id_strings = j.at("playerIds").get<std::vector<std::string>>();
    std::vector<PlayerId> playerIds;
    playerIds.reserve(player_id_strings.size());
    for (const auto str: player_id_strings) {
        playerIds.push_back(PlayerId(str));
    }

    std::vector<std::string> audience_id_strings = j.at("audienceIds").get<std::vector<std::string>>();
    std::vector<AudienceId> audienceIds;
    audienceIds.reserve(audience_id_strings.size());
    for (const auto str: audience_id_strings) {
        audienceIds.push_back(AudienceId(str));
    }

    GameRoom room(
            id,
            j.at("gameName").get<std::string>(),
            j.at("gameConfig"),
            *maybeGameStatus,
            playerIds,
            audienceIds);

    return room;
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
        GameStatus status,
        const std::vector<PlayerId> &player_ids,
        const std::vector<AudienceId> &audience_ids)
        : id(id), game_name(game) {
    game_config = config;
    game_status = status;
    this->player_ids = player_ids;
    this->audience_ids = audience_ids;
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

std::vector<PlayerId> GameRoom::get_players() const{
    return player_ids;
}

std::vector<AudienceId> GameRoom::get_audiences() const{
    return audience_ids;
}

std::string GameRoom::serialized() const {
    nlohmann::json j = *this;
    return j.dump();
}

bool GameRoom::operator== (const GameRoom &other) const {
    return other.id == this->id;
}

GameRoom GameRoom::with_config(const nlohmann::json& config) const {
    GameRoom new_room(this->id, this->game_name, config, this->game_status,
                      this->player_ids, this->audience_ids);
    return new_room;
}

GameRoom GameRoom::with_game_status(GameStatus status) const {
    GameRoom new_room(this->id, this->game_name, this->game_config, status,
                      this->player_ids, this->audience_ids);
    return new_room;
}

GameRoom GameRoom::with_player_id(const PlayerId player_id) const {
    std::vector<PlayerId> new_player_ids = get_players();
    new_player_ids.push_back(player_id);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, new_player_ids, this->audience_ids);
    return new_room;
}

GameRoom GameRoom::with_audience_id(const AudienceId audience_id) const {
    std::vector<AudienceId> new_audience_ids = get_audiences();
    new_audience_ids.push_back(audience_id);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, new_audience_ids);
    return new_room;
}