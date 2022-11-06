#include "ContentVariant.h"
#include <unordered_map>

using namespace std;

class AudienceMember {
public:
    string const name;
        AudienceMember(string audienceMemberName);
        void addContent(string key, dataBucket content);
        dataBucket getContent(string key);

    private:
        unordered_map<string, dataBucket> audienceContents;
};