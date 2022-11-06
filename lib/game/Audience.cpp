#include "include/Audience.h"

using namespace std;

AudienceMember::AudienceMember(string audienceMemberName)
: name(audienceMemberName) {}

void AudienceMember::addContent(string key, dataBucket content) {
    audienceContents[key] = content;
}

dataBucket AudienceMember::getContent(string key) {
    return audienceContents.find(key)->second;
}