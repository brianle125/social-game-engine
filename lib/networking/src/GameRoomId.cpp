//
// Created by Yiwen Wang on 2022-10-23.
//

#include "GameRoomId.h"

GameRoomId::GameRoomId(const std::string& id){
    value = id;
}

GameRoomId::GameRoomId(const boost::uuids::uuid &id){
    //value = boost::lexical_cast<std::string>(id);
    value = boost::uuids::to_string(id);
}

std::string GameRoomId::get_value() const {
    return value;
}

bool GameRoomId::operator== (const GameRoomId &other) const {
    return this->value == other.value;
}