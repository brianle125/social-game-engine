//
// Created by Yiwen Wang on 2022-11-20.
//

#include "PlayerId.h"
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

PlayerId::PlayerId(const std::string& id){
    value = id;
}

PlayerId::PlayerId(std::string&& id){
    value = id;
}

PlayerId::PlayerId(const boost::uuids::uuid &id){
    value = boost::uuids::to_string(id);
}

std::string PlayerId::get_value() const {
    return value;
}

bool PlayerId::operator== (const PlayerId &other) const {
    return this->value == other.value;
}
