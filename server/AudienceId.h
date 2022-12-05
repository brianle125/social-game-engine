//
// Created by Yiwen Wang on 2022-11-21.
//

#ifndef PROJECT_AUDIENCEID_H
#define PROJECT_AUDIENCEID_H

#include <string>
#include <boost/uuid/uuid.hpp>

class AudienceId{
    private:
        std::string value;
    public:
    AudienceId(const std::string&);
    AudienceId(std::string&&);
    AudienceId(const boost::uuids::uuid &);
    std::string get_value() const;
    bool operator== (const AudienceId &other) const;
};

#endif //PROJECT_AUDIENCEID_H
