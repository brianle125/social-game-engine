//
// Created by Yiwen Wang on 2022-11-23.
//

#include "GUITask.h"
#include <iostream>

GUITask::GUITask(const std::string& value, const Id& task_id): task_id(task_id){
    this->value = value;
}
GUITask::GUITask(std::string&& value, Id&& task_id): task_id(task_id){
    this->value = value;
}

std::string GUITask::get_value() const{
    std::cout << "get_value:" << std::endl;
    return value;
}

Id GUITask::get_task_id() const{
    return task_id;
}

bool GUITask::operator== (const GUITask &other) const{
    return this->task_id == other.task_id;
}


void to_json(nlohmann::json& j, const GUITask& t) {
    j = nlohmann::json{
            {"value", t.get_value()},
            {"GUITaskId", t.get_task_id().get_value()},
    };
}

GUITask GUITask::from_json(const nlohmann::json &j) {

    std::string value = j["value"].get<std::string>();
    std::string task_id = j["GUITaskId"].get<std::string>();
    Id id(task_id);

    GUITask t(value, id);
    return t;
}

std::string GUITask::serialized() const{
    nlohmann::json j = *this;
    return j.dump();
}