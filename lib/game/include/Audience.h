#include "ContentVariant.h"
#include <unordered_map>

using namespace std;

class AudienceMember {
public:
    string const name;
        AudienceMember(string audienceMemberName);
        void addContent(string key, myVariant content);
        myVariant getContent(string key);

    private:
        unordered_map<string, myVariant> audienceContents;
};