#include "crow_all.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include "GameRoomId.h"

void store_game_room(GameRoomId game_room_id){
    //not implement

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

    app.port(18080).multithreaded().run();
}