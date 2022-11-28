//
// Created by Yiwen Wang on 2022-11-23.
//

#ifndef SERVER_ID_H
#define SERVER_ID_H
#include <string>
#include <boost/uuid/uuid.hpp>

class Id {
private:
    std::string value;
public:
    Id(const std::string&);
    Id(std::string&&);
    Id(const boost::uuids::uuid &);
    std::string get_value() const;
    bool operator== (const Id &other) const;
};


#endif //SERVER_ID_H
