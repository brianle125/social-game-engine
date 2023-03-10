#include <optional>
#include "crow_all.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include "GameRoomId.h"
#include "PlayerId.h"
#include "AudienceId.h"
#include "GameRoom.h"
#include "GameStatus.h"
#include "RoundNumber.h"
#include "GUITask.h"
#include "Message.h"
#include "PlayerInput.h"

namespace fs = std::filesystem;

std::string to_game_room_storge_name(const GameRoomId& id) {
    fs::create_directory("game_room_database");
    return "game_room_database/" + id.get_value() + ".json";
}

void store_game_room(GameRoom game_room){
    std::ofstream myfile;
    auto id = game_room.get_game_room_id();

    myfile.open(to_game_room_storge_name(id));
    myfile << game_room.serialized();

    myfile.close();
}

std::optional<GameRoom> get_game_room(GameRoomId id){

    std::ifstream f(to_game_room_storge_name(id));
    if (!f.good()) {
        return {};
    }

    nlohmann::json data = nlohmann::json::parse(f);
    return GameRoom::from_json(data);
}


std::optional<GameRoom> update_game_room(const GameRoom &room) {
    auto maybeRoom = get_game_room(room.get_game_room_id());
    if (!maybeRoom) {
        return {};
    }

    store_game_room(room);

    auto updatedRoom = get_game_room(room.get_game_room_id());

    return updatedRoom;
}

crow::response fetch_game_room_route(const std::string game_room_id) {
    auto maybeRoom = get_game_room(GameRoomId(game_room_id));
    if (!maybeRoom) {
        return crow::response(crow::status::NOT_FOUND);
    }
    return crow::response(crow::status::OK, "json", maybeRoom->serialized());
}


crow::response create_empty_game_room_route(const crow::request &req) {
    //expect client respond: a string, e.g. "CoinGame"
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body"); // same as crow::response(400)
    }
    try {
        auto gameName = x["gameName"].s();//get a game name
        std::cout << "game name: " << gameName << std::endl;

        auto uuid = boost::uuids::random_generator()();
        GameRoomId id(uuid);
        GameRoom gameRoom(id, gameName);
        store_game_room(gameRoom);
        //return a invitation code
        return crow::response{id.get_value()};
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

/**
 * Take a request that specifies the configuration of a game,
 * and create a game instance/room for that game.
 * @param req a json object having 2 keys: "id" and "config"
 * @return an http response
 */
crow::response save_game_room_config_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body"); // same as crow::response(400)
    }

    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        nlohmann::json game_config = payload["config"];
        std::cout << game_config << std::endl;

        auto new_room = room->with_config(game_config);
        auto updated_room = update_game_room(new_room);

        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

crow::response change_game_status_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body"); // same as crow::response(400)
    }

    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        std::string game_status_key = payload["status"];
        std::cout << game_status_key << std::endl;

        auto game_status = GameStatus::try_parse(game_status_key);
        if (!game_status) {
            return crow::response(crow::status::BAD_REQUEST, "invalid game status: " + game_status_key);
        }

        auto new_room = room->with_game_status(*game_status);
        auto updated_room = update_game_room(new_room);

        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }

}

crow::response add_player_to_game_room_route(const crow::request &req) {
    // TBD
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body");
    }
    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        auto playerId = x["playerIds"].s();//get a player id
        PlayerId p_id(playerId);

        for (const auto playerId: room->get_players()) {
            if(p_id == playerId){//duplicate
                return crow::response(crow::status::NOT_FOUND, "this player already join the game room");
            }
        }


        auto new_room = room->with_player_id(p_id);
        auto updated_room = update_game_room(new_room);

        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}


crow::response add_audience_to_game_room_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body");
    }
    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        auto audienceId = x["audienceIds"].s();//get a audience id
        AudienceId a_id(audienceId);

        for (const auto audienceId: room->get_audiences()) {
            if(a_id == audienceId){//duplicate
                return crow::response(crow::status::NOT_FOUND, "this audience already join the game room");
            }
        }

        for (const auto playerId: room->get_players()) {
            if(a_id.get_value() == playerId.get_value()){//duplicate
                return crow::response(crow::status::NOT_FOUND, "player can not join room as an audience");
            }
        }

        auto new_room = room->with_audience_id(a_id);
        auto updated_room = update_game_room(new_room);

        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

crow::response add_GUI_task_to_game_room_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body");
    }
    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        nlohmann::json GUI_json = payload["GUITask"];
        std::cout << GUI_json << std::endl;

        std::cout << "GUI " << GUI_json.size() << std::endl;

        auto GUI_task = GUITask::from_json(GUI_json);
        auto new_room = room->with_GUI_task(GUI_task);
        std::cout << "GUI " << new_room.get_GUI_tasks()[0].get_value() << std::endl;
        auto updated_room = update_game_room(new_room);
        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }
        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

crow::response add_message_to_game_room_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body");
    }
    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }
        nlohmann::json message_json = payload["message"];
        std::cout << message_json << std::endl;

        std::cout << "message " << message_json.size() << std::endl;

        auto message = Message::from_json(message_json);
        auto new_room = room->with_message(message);
        std::cout << "message string:" << new_room.get_messages()[0].get_message_str() << std::endl;
        auto updated_room = update_game_room(new_room);
        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

crow::response add_player_input_to_game_room_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body");
    }
    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        nlohmann::json input_json = payload["playerInput"];
        std::cout << input_json << std::endl;

        std::cout << "playerInput " << input_json.size() << std::endl;

        auto input = PlayerInput::from_json(input_json);
        auto new_room = room->with_player_input(input);
        std::cout << "playerInput string:"<< std::endl;
        auto updated_room = update_game_room(new_room);
        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

crow::response add_round_number_to_game_room_route(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST, "missing body");
    }
    try {
        nlohmann::json payload = nlohmann::json::parse(req.body);
        std::string id = payload["id"];
        GameRoomId roomID(id);
        auto room = get_game_room(roomID);
        if (!room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found");
        }

        auto round_num = payload["roundNumber"];//get roundNumber
        RoundNumber r_num(round_num);

        auto new_room = room->with_round_number(r_num);
        auto updated_room = update_game_room(new_room);

        if (!updated_room) {
            return crow::response(crow::status::NOT_FOUND, "game room not found while being updated");
        }

        return crow::response(crow::status::OK, "json", updated_room->serialized());
    } catch (const std::exception& ex) {
        return crow::response(crow::status::BAD_REQUEST, ex.what());
    }
}

int main() {
    std::cout << "hello world" << std::endl;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    CROW_ROUTE(app, "/game-rooms")
            .methods("POST"_method)
                    (create_empty_game_room_route);

    CROW_ROUTE(app, "/game-rooms/<string>")(fetch_game_room_route);

    CROW_ROUTE(app, "/game-room-configs")
            .methods("POST"_method)
                    (save_game_room_config_route);

    CROW_ROUTE(app, "/game-room-statuses")
            .methods("POST"_method)
                    (change_game_status_route);

    CROW_ROUTE(app, "/player-join-room")
            .methods("POST"_method)
                    (add_player_to_game_room_route);

    CROW_ROUTE(app, "/audience-join-room")
            .methods("POST"_method)
                    (add_audience_to_game_room_route);

    CROW_ROUTE(app, "/add-GUI-task")
            .methods("POST"_method)
                    (add_GUI_task_to_game_room_route);

    CROW_ROUTE(app, "/add-message")
            .methods("POST"_method)
                    (add_message_to_game_room_route);

    CROW_ROUTE(app, "/add-player-input")
            .methods("POST"_method)
                    (add_player_input_to_game_room_route);

    CROW_ROUTE(app, "/add-round-number")
            .methods("POST"_method)
                    (add_round_number_to_game_room_route);

    app.port(18080).run();
}