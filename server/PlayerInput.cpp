//
// Created by Yiwen Wang on 2022-11-23.
//

#include "PlayerInput.h"
PlayerInput::PlayerInput(const std::string& value, const std::string& round_number, const std::string& type){
    this->value = value;
    this->round_number = round_number;
    this->type = type;
}

PlayerInput::PlayerInput(std::string&& value,std::string&& round_number,std::string&& type){
    this->value = value;
    this->round_number = round_number;
    this->type = type;
}

std::string PlayerInput::get_value() const {
    return value;
}

std::string PlayerInput::get_type() const{
    return type;
}
std::string PlayerInput::get_round_number() const{
    return round_number;
}

void to_json(nlohmann::json& j, const PlayerInput& p) {
    j = nlohmann::json{
            {"value", p.get_value()},
            {"type", p.get_type()},
            {"roundNumber", p.get_round_number()}
    };
}

PlayerInput PlayerInput::from_json(const nlohmann::json &j) {
    std::string value = j["value"];
    std::string type = j["type"];
    std::string round_number = j["roundNumber"];

    PlayerInput p(value, round_number, type);
    return p;
}

std::string PlayerInput::serialized() const{
    nlohmann::json j = *this;
    return j.dump();
}