//
// Created by Yiwen Wang on 2022-10-23.
//

#include "GameRoom.h"
#include <iostream>
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

    // TBD: this is wrong
    std::vector <nlohmann::json> GUI_task_serialized;
    for (const auto Task: g.get_GUI_tasks()) {
        GUI_task_serialized.push_back(nlohmann::json::parse(Task.serialized()));
    }

    std::vector<nlohmann::json> message_serialized;
    for (const auto Message: g.get_messages()) {
        message_serialized.push_back(nlohmann::json::parse(Message.serialized()));
    }

    std::vector <nlohmann::json> player_input_serialized;

    for (const auto Inputs: g.get_player_inputs()) {
        player_input_serialized.push_back(nlohmann::json::parse(Inputs.serialized()));
    }


    j["id"] = g.get_game_room_id().get_value();
    j["gameName"] = g.get_game_name(),
    j["gameConfig"] = game_config ? *game_config : nlohmann::json(),
    j["gameStatus"] = g.get_game_status().get_value();
    j["playerIds"] = player_id_strings;
    j["audienceIds"] = audience_id_strings;
    j["roundNumber"] =  g.get_round_number().get_value();
    j["GUITask"] =  GUI_task_serialized;
    j["message"] = message_serialized;
    j["playerInput"] = player_input_serialized;

}

std::optional <GameRoom> GameRoom::from_json(const nlohmann::json &j) {
    std::string gameStatusString = j.at("gameStatus").get<std::string>();
    std::optional<GameStatus> maybeGameStatus = GameStatus::try_parse(gameStatusString);
    if (!maybeGameStatus){
        throw std::invalid_argument("invalid gameStatus: " + gameStatusString);
    }
    GameRoomId id(j.at("id").get<std::string>());

    std::vector<PlayerId> playerIds;
    auto maybe_playerIds = j.find("playerIds");
    if (maybe_playerIds != j.end()) {
        std::vector<std::string> player_id_strings = maybe_playerIds->get<std::vector<std::string>>();
        playerIds.reserve(player_id_strings.size());
        for (const auto str: player_id_strings) {
            playerIds.push_back(PlayerId(str));
        }
    }

    std::vector<AudienceId> audienceIds;
    auto maybe_audience_id = j.find("audienceIds");
    if(maybe_audience_id != j.end()) {
        std::vector<std::string> audience_id_strings = maybe_audience_id->get<std::vector<std::string>>();
        for (const auto str: audience_id_strings) {
            audienceIds.push_back(AudienceId(str));
        }
    }

    std::string roundNumber;
    auto maybe_round_number = j.find("roundNumber");
    if(maybe_round_number != j.end()) {
        roundNumber = maybe_round_number->get<std::string>();
    }


    std::vector<GUITask> GUI_tasks;
    auto maybe_GUI_task = j.find("GUITask");
    if(maybe_GUI_task != j.end()) {
        std::vector<nlohmann::json> GUI_task_json = maybe_GUI_task->get<std::vector<nlohmann::json>>();
        for (const auto json: GUI_task_json) {
            GUITask t = GUITask::from_json(json);
            GUI_tasks.push_back(t);
        }
    }

    std::vector<Message> messages;
    auto maybe_message = j.find("message");
    if(maybe_message != j.end()) {
        std::vector<nlohmann::json> message_json = maybe_message->get<std::vector<nlohmann::json>>();
        for (const auto json: message_json) {
            Message t = Message::from_json(json);
            messages.push_back(t);
        }
    }

    std::vector<PlayerInput> player_inputs;
    auto maybe_player_inputs = j.find("playerInput");
    if(maybe_player_inputs != j.end()) {
        std::vector<nlohmann::json> player_input_json = maybe_player_inputs->get<std::vector<nlohmann::json>>();
        for (const auto json: player_input_json) {
            PlayerInput t = PlayerInput::from_json(json);
            player_inputs.push_back(t);
        }
    }


    GameRoom room(
            id,
            j["gameName"].get<std::string>(),
            j.at("gameConfig"),
            *maybeGameStatus,
            playerIds,
            audienceIds,
            roundNumber,
            GUI_tasks,
            messages,
            player_inputs);

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
        const std::vector<AudienceId> &audience_ids,
        const RoundNumber& round_number,
        const std::vector<GUITask> & GUI_task,
        const std::vector<Message> & messages,
        const std::vector<PlayerInput> & player_inputs)
        : id(id), game_name(game) {
    game_config = config;
    game_status = status;
    this->player_ids = player_ids;
    this->audience_ids = audience_ids;
    this->round_number = round_number;
    this->GUI_tasks = GUI_task;
    this->messages = messages;
    this->player_inputs = player_inputs;

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

RoundNumber GameRoom::get_round_number() const{
    return round_number;
}
std::vector<GUITask> GameRoom::get_GUI_tasks() const{
    return GUI_tasks;
}
std::vector<Message> GameRoom::get_messages() const{
    return messages;
}
std::vector<PlayerInput> GameRoom::get_player_inputs() const{
    return player_inputs;
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
                      this->player_ids, this->audience_ids, this->round_number,
                      this->GUI_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_game_status(GameStatus status) const {
    GameRoom new_room(this->id, this->game_name, this->game_config, status,
                      this->player_ids, this->audience_ids, this->round_number,
                      this->GUI_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_player_id(const PlayerId player_id) const {
    std::vector<PlayerId> new_player_ids = get_players();
    new_player_ids.push_back(player_id);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, new_player_ids, this->audience_ids,
                      this->round_number,
                      this->GUI_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_audience_id(const AudienceId audience_id) const {
    std::vector<AudienceId> new_audience_ids = get_audiences();
    new_audience_ids.push_back(audience_id);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, new_audience_ids,
                      this->round_number,
                      this->GUI_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_round_number(const RoundNumber round_number) const{
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, this->audience_ids,
                      round_number,
                      this->GUI_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_GUI_task(const GUITask GUI_task) const{
    std::vector<GUITask> new_tasks = get_GUI_tasks();
    new_tasks.push_back(GUI_task);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, this->audience_ids,
                      this->round_number,
                      new_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_message(const Message message) const{
    std::vector<Message> new_messages = get_messages();
    new_messages.push_back(message);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, this->audience_ids,
                      this->round_number,
                      this->GUI_tasks, new_messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::with_player_input(const PlayerInput player_input) const{
    std::vector<PlayerInput> new_inputs = get_player_inputs();
    new_inputs.push_back(player_input);
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, this->audience_ids,
                      this->round_number,
                      this->GUI_tasks, this->messages, new_inputs);
    return new_room;
}

GameRoom GameRoom::delete_GUI_task(const Id GUI_task_id) const{
    std::vector<GUITask> tasks;
    for(int i = 0; i< GUI_tasks.size(); i++){
        if(!(GUI_tasks[i].get_task_id() == GUI_task_id)){
            tasks.push_back(GUI_tasks[i]);
        }
    }
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, this->audience_ids,
                      this->round_number,
                      GUI_tasks, this->messages, this->player_inputs);
    return new_room;
}

GameRoom GameRoom::delete_message(const Id message_id) const{
    std::vector<Message> m;
    for(int i = 0; i< messages.size(); i++){
        if(!(messages[i].get_message_id() == message_id)){
            m.push_back(messages[i]);
        }
    }
    GameRoom new_room(this->id, this->game_name, this->game_config,
                      this->game_status, this->player_ids, this->audience_ids,
                      this->round_number,
                      this->GUI_tasks, messages, this->player_inputs);
    return new_room;

}
