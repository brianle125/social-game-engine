#include <VariantParser.h>
#include <iostream>

using namespace std;

dataVariant VariantParser::makeVariantFromJson(const json& j) {
	nlohmann::detail::value_t variableType = j.type();
	dataVariant data;

	switch (variableType) {
	case nlohmann::detail::value_t::string:
		data = dataVariant(j.get<string>());
		break;
	
	case nlohmann::detail::value_t::boolean:
		data = dataVariant(j.get<bool>());
		break;

	case nlohmann::detail::value_t::number_integer:
		data = dataVariant(j.get<int>());
		break;
	
	case nlohmann::detail::value_t::number_float:
		data = dataVariant(j.get<float>());
		break;

	case nlohmann::detail::value_t::array:
		cout << "Array Found\n";
		data = makeVariantVectorFromJson(j);
		break;

	case nlohmann::detail::value_t::object:
		cout << "Object Found\n";
		data = makeVariantMapFromJson(j);
		break;

	default:
		break;
	}

	return data;
}

dataVariant VariantParser::makeVariantVectorFromJson(const json& j) {
	vector<dataVariant> internalData;
	for(auto& item : j.items()) {
		internalData.push_back(makeVariantFromJson(item.value()));
	}
	return dataVariant(internalData);
}

dataVariant VariantParser::makeVariantMapFromJson(const json& j) {
	map<string, dataVariant> internalData;
	for(auto& item : j.items()) {
		string key = item.key();
		dataVariant variant = makeVariantFromJson(item.value());
		internalData.emplace(key, variant);
	}
	return dataVariant(internalData);
}