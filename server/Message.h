//
// Created by Yiwen Wang on 2022-11-23.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H
#include "Id.h"
#include <nlohmann/json.hpp>

class Message {
private:
    Id message_id;
    std::string receiver_id;
    std::string message_str;

public:
    static Message from_json(const nlohmann::json &j);

    Message(const Id&, const std::string&, const std::string&);
    Message(Id&&, std::string&&, std::string&&);
    std::string get_receiver_id() const;
    std::string get_message_str() const;
    Id get_message_id() const;
    bool operator==(const Message &other) const;
    std::string serialized() const;
};


#endif //SERVER_MESSAGE_H
