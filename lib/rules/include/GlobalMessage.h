#pragma once
#include "IRule.h"
#include <string>

class GlobalMessage final : public rules::IRule {   
public:
    GlobalMessage(std::string message);
    void executeRule() override;

private:
    std::string message;
};