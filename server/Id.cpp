//
// Created by Yiwen Wang on 2022-11-23.
//

#include "Id.h"
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

Id::Id(const std::string& id){
    value = id;
}

Id::Id(std::string&& id){
    value = id;
}

Id::Id(const boost::uuids::uuid &id){
    value = boost::uuids::to_string(id);
}

std::string Id::get_value() const {
    return value;
}

bool Id::operator== (const Id &other) const {
    return this->value == other.value;
}