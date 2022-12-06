#pragma once

#include <string>
#include <chrono>

namespace rules {
    class InputRule {
    public:
        enum InputValidation { success, failure };
        virtual InputValidation receiveResponse(std::string message, std::chrono::duration<double> duration) = 0;
    };
}
