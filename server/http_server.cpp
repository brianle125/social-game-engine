#include <optional>
#include "crow_all.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include "GameRoomId.h"
#include "GameRoom.h"
#include "GameStatus.h"
namespace fs = std::filesystem;

std::unordered_map<GameRoomId, GameRoom, GameRoomIdHashFunction> gameRooms;

std::string to_game_room_storge_name(const GameRoomId& id) {
    fs::create_directory("game_room_database");
    return "game_room_database/" + id.get_value() + ".json";
}

void store_game_room(GameRoom game_room){
    std::ofstream myfile;
    auto id = game_room.get_game_room_id();

    myfile.open(to_game_room_storge_name(id));
    myfile << game_room.serialized();

    gameRooms.insert({game_room.get_game_room_id(), game_room});
    myfile.close();
}

std::optional<GameRoom> get_game_room(GameRoomId id){
    auto itr = gameRooms.find(id);
    if (itr == gameRooms.end()){
        //catch error
        return {};
    }else{
        return itr->second;
    }
}

std::optional<GameRoom> update_game_room(const GameRoom &room) {
    auto itr = gameRooms.find(room.get_game_room_id());
    if(itr == gameRooms.end()){
        return {};
    }
    itr->second = room;

    auto itr_2 = gameRooms.find(room.get_game_room_id());
    if(itr_2 == gameRooms.end()){
        return {};
    } else {
        return itr_2->second;
    }
}

crow::response fetch_game_room_route(const std::string game_room_id) {
    auto iter = gameRooms.find(game_room_id);
    if (iter == gameRooms.end()){
        return crow::response(crow::status::NOT_FOUND);
    }

    return crow::response(crow::status::OK, "json", iter->second.serialized());
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

void join_a_room() {
    // TBD
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

    app.port(18080).run();
}