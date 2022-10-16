#pragma once

#include <string>

namespace rules {
    class InputRule {
    public:
        virtual void getInput() = 0;
        virtual bool receiveResponse(std::string message) = 0;
    };
}
