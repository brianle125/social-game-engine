#pragma once

#include <nlohmann/json.hpp>
#include <ContentVariant.h>

using namespace std;
using json = nlohmann::json;

class VariantParser {
public:
    dataVariant makeVariantFromJson(const json &j);

private:

};