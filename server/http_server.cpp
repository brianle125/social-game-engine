#include <optional>
#include "crow_all.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include "GameRoomId.h"
#include "GameRoom.h"
#include <nlohmann/json.hpp>


//global hash to contain all invitation code
std::unordered_map<GameRoomId, GameRoom, GameRoomIdHashFunction> gameRooms;

void store_game_room(GameRoom game_room){
    //not implement
    gameRooms.insert({game_room.get_game_room_id(), game_room});
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

    return crow::response(iter->second.serialized());
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
    //expect client respond: a string, e.g. "CoinGame"
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
            return crow::response(crow::status::NOT_FOUND);
        }

        nlohmann::json game_config = payload["config"];
        std::cout << game_config << std::endl;

        return crow::response(crow::status::OK);
    }catch (const std::exception& ex) {
        nlohmann::json dude = nlohmann::json::parse(req.body);
        std::cout << "dude id: " << dude["id"] << std::endl;
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

    app.port(18080).run();
}