//
// Created by Yiwen Wang on 2022-11-23.
//

#ifndef SERVER_GUITASK_H
#define SERVER_GUITASK_H
#include <boost/uuid/uuid_generators.hpp> // generators
#include "Id.h"
#include <nlohmann/json.hpp>

class GUITask {
private:
    Id task_id;
    std::string value;

public:
    static GUITask from_json(const nlohmann::json &j);

    GUITask(const std::string&, const Id&);
    GUITask(std::string&&, Id&&);
    std::string get_value() const;
    Id get_task_id() const;
    bool operator== (const GUITask &other) const;
    std::string serialized() const;
};


#endif //SERVER_GUITASK_H
