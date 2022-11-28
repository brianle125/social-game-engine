//
// Created by Yiwen Wang on 2022-11-21.
//
#include "AudienceId.h"
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

AudienceId::AudienceId(const std::string& id){
    value = id;
}

AudienceId::AudienceId(std::string&& id){
    value = id;
}

AudienceId::AudienceId(const boost::uuids::uuid &id){
    value = boost::uuids::to_string(id);
}

std::string AudienceId::get_value() const {
    return value;
}

bool AudienceId::operator== (const AudienceId &other) const {
    return this->value == other.value;
}
