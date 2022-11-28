//
// Created by Yiwen Wang on 2022-11-23.
//

#ifndef SERVER_ROUNDNUMBER_H
#define SERVER_ROUNDNUMBER_H
#include <string>

class RoundNumber {
private:
    std::string value;
public:
    RoundNumber();
    RoundNumber(const std::string&);
    RoundNumber(std::string&&);
    std::string get_value() const;
    bool operator== (const RoundNumber &) const;
};


#endif //SERVER_ROUNDNUMBER_H
