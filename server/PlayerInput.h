//
// Created by Yiwen Wang on 2022-11-23.
//

#ifndef SERVER_PLAYERINPUT_H
#define SERVER_PLAYERINPUT_H
#include <nlohmann/json.hpp>
#include "Id.h"
class PlayerInput {
private:
    std::string type;
    std::string value;
    std::string round_number;
public:
    static PlayerInput from_json(const nlohmann::json &j);

    PlayerInput(const std::string&, const std::string&, const std::string&);
    PlayerInput(std::string&&,std::string&&,std::string&&);
    std::string get_value() const;
    std::string get_type() const;
    std::string get_round_number() const;
    std::string serialized() const;
};


#endif //SERVER_PLAYERINPUT_H
