#include "crow_all.h"

crow::response create_game(const crow::request &req) {
    auto x = crow::json::load(req.body);
    if (!x) {
        return crow::response(crow::status::BAD_REQUEST); // same as crow::response(400)
    }
    try {
        auto gameName = x["gameName"].s();
        //
        return crow::response{gameName};
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