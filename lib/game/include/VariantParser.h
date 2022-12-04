#pragma once

#include <nlohmann/json.hpp>
#include <string_view>
#include <ContentVariant.h>

using json = nlohmann::json;

class VariantParser {
public:
    dataVariant makeVariantFromJson(const json& j);

    std::vector<string_view> getKeysFromString(const string_view toParse);

private:
    dataVariant makeVariantVectorFromJson(const json& j);
    dataVariant makeVariantMapFromJson(const json& j);
};
