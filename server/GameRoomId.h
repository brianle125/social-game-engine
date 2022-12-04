//
// Created by Yiwen Wang on 2022-10-23.
//

#ifndef HTTP_SERVER_CPP_GAMEROOMID_H
#define HTTP_SERVER_CPP_GAMEROOMID_H
#include <string>
#include <boost/uuid/uuid.hpp>            // uuid class

class GameRoomId {
private:
    std::string value;
public:
    GameRoomId(const std::string&);
    GameRoomId(std::string&&);
    GameRoomId(const boost::uuids::uuid &);
    std::string get_value() const;
    bool operator== (const GameRoomId &other) const;
};

class GameRoomIdHashFunction {
public:
    std::size_t operator()(const GameRoomId& game_room_id) const {
        return std::hash<std::string>()(game_room_id.get_value());
    }
};

#endif //HTTP_SERVER_CPP_GAMEROOMID_H
