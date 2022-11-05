#pragma once

#include <string>
#include <chrono>

namespace rules {
    class InputRule {
    public:
        enum InputValidation { success, failure };
        virtual void getInput() = 0;
        virtual InputValidation receiveResponse(std::string message, std::chrono::system_clock::time_point start) = 0;
    };
}
