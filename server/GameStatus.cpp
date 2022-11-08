//
// Created by Yiwen Wang on 2022-11-07.
//

#include "GameStatus.h"

GameStatus::GameStatus(const std::string& value) {
    this->value = value;
}

GameStatus::GameStatus(std::string&& value) {
    this->value = value;
}

std::string GameStatus::get_value() const {
    return value;
}

std::optional<GameStatus> GameStatus::try_parse(std::string value) {
    if (value == "not_started"
        || value == "running"
        || value == "paused"
        || value == "terminated"
        || value == "error") {
        return GameStatus(value);
    }

    return {};
}

bool GameStatus::operator== (const GameStatus &other) const {
    return this->value == other.value;
}

const GameStatus GameStatus::not_started("not_started");
const GameStatus GameStatus::running("running");
const GameStatus GameStatus::paused("paused");
const GameStatus GameStatus::terminated("terminated");
const GameStatus GameStatus::error("error");
