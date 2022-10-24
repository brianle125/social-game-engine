//
// Created by Yiwen Wang on 2022-10-23.
//

#ifndef HTTP_SERVER_CPP_GAMEROOMID_H
#define HTTP_SERVER_CPP_GAMEROOMID_H
#include <iostream>
#include <string>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

class GameRoomId {
private:
    std::string value;
public:
    GameRoomId(const std::string&);
    GameRoomId(const boost::uuids::uuid &);
    std::string get_value();
};


#endif //HTTP_SERVER_CPP_GAMEROOMID_H
