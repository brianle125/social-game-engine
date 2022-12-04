//
// Created by Yiwen Wang on 2022-11-23.
//

#include "Message.h"

Message::Message(const Id& message_id,
                 const std::string& receiver_id,
                 const std::string& message_str):
                 message_id(message_id) {
    this->receiver_id = receiver_id;
    this->message_str = message_str;
}

Message::Message(Id&& message_id,
                 std::string&& receiver_id,
                 std::string&& message_str):message_id(message_id){
    this->receiver_id = receiver_id;
    this->message_str = message_str;
}
std::string Message::get_receiver_id() const{
    return receiver_id;
}

std::string Message::get_message_str() const{
    return message_str;
}

Id Message::get_message_id() const{
    return message_id;
}

bool Message::operator==(const Message &other) const{
    return (this->message_id == other.get_message_id());
}

void to_json(nlohmann::json& j, const Message& m) {
    j = nlohmann::json{
            {"messageId", m.get_message_id().get_value()},
            {"receiverId", m.get_receiver_id()},
            {"messageStr", m.get_message_str()}
    };
}

Message Message::from_json(const nlohmann::json &j) {
    std::string messageId = j["messageId"];
    Id id(messageId);
    std::string receiverId = j["receiverId"];
    std::string messageStr = j["messageStr"];

    Message m(id, receiverId, messageStr);
    return m;
}

std::string Message::serialized() const{
    nlohmann::json j = *this;
    return j.dump();
}