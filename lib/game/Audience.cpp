#include "include/Audience.h"

using namespace std;

AudienceMember::AudienceMember(string audienceMemberName)
: name(audienceMemberName) {}

void AudienceMember::addContent(string key, dataVariant content) {
    audienceContents[key] = content;
}

dataVariant AudienceMember::getContent(string key) {
    return audienceContents.find(key)->second;
}