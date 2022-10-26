#include "crow_all.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include "GameRoomId.h"
#include "GameRoom.h"

//global hash to contain all invitation code
std::unordered_map<GameRoomId, GameRoom, GameRoomIdHashFunction> gameRooms;
void store_game_room(GameRoom game_room){
    //not implement
    gameRooms.insert({game_room.get_game_room_id(), game_room});
}

crow::response get_game_room(const std::string game_room_id) {
    auto iter = gameRooms.find(game_room_id);
    if (iter == gameRooms.end()){
        return crow::response(crow::status::NOT_FOUND);
    }

    return crow::response(iter->second.serialized());
}

crow::response create_game(const crow::request &req) {
    //expect client respond: a string, e.g. "CoinGame"
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST); // same as crow::response(400)
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
        return crow::response(crow::status::BAD_REQUEST);
    }
}

void create_a_game_with_Json() {

}

void join_a_room() {

}

int main() {
    std::cout << "hello world" << std::endl;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    CROW_ROUTE(app, "/game-rooms")
            .methods("POST"_method)
                    (create_game);

    CROW_ROUTE(app, "/game-rooms/<string>")(get_game_room);

    app.port(18080).run();
}