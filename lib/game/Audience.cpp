#include "include/Audience.h"

using namespace std;

AudienceMember::AudienceMember(string audienceMemberName)
: name(audienceMemberName) {}

void AudienceMember::addContent(string key, myVariant content) {
    audienceContents[key] = content;
}

myVariant AudienceMember::getContent(string key) {
    return audienceContents.find(key)->second;
}