#pragma once

#include <string>
#include <chrono>

namespace rules {
    class InputRule {
    public:
        virtual void getInput() = 0;
        virtual bool receiveResponse(std::string message, std::chrono::system_clock::time_point start) = 0;
    };
}
