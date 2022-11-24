//
// Created by Yiwen Wang on 2022-11-23.
//

#include "RoundNumber.h"

RoundNumber::RoundNumber() {
    this->value = "0";
}

RoundNumber::RoundNumber(const std::string& value) {
    this->value = value;
}

RoundNumber::RoundNumber(std::string&& value) {
    this->value = value;
}

std::string RoundNumber::get_value() const {
    return value;
}

bool RoundNumber::operator== (const RoundNumber &other) const {
    return this->value == other.value;
}