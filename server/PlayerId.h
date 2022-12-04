//
// Created by Yiwen Wang on 2022-11-20.
//

#ifndef PROJECT_PLAYERID_H
#define PROJECT_PLAYERID_H
#include <string>
#include <boost/uuid/uuid.hpp>

class PlayerId {
private:
    std::string value;
public:
    PlayerId(const std::string&);
    PlayerId(std::string&&);
    PlayerId(const boost::uuids::uuid &);
    std::string get_value() const;
    bool operator== (const PlayerId &other) const;
};


#endif //PROJECT_PLAYERID_H
