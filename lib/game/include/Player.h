#pragma once

#include <string>
#include <unordered_map>
#include "ContentVariant.h"
#include "Server.h"

using namespace std;

class Player {
    public:
        string const name;
        networking::Connection connection;
        Player(string playerName);
        void addContent(string key, myVariant content);
        myVariant getContent(string key);

    private:
        unordered_map<string, myVariant> playerContents;     
};