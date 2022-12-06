#include <VariantParser.h>
#include <iostream>

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
		data = makeVariantVectorFromJson(j);
		break;

	case nlohmann::detail::value_t::object:
		data = makeVariantMapFromJson(j);
		break;

	default:
		break;
	}

	return data;
}

dataVariant VariantParser::makeVariantVectorFromJson(const json& j) {
	std::vector<dataVariant> internalData;
	for(auto& item : j.items()) {
		internalData.push_back(makeVariantFromJson(item.value()));
	}
	return dataVariant(internalData);
}

dataVariant VariantParser::makeVariantMapFromJson(const json& j) {
	std::map<string, dataVariant> internalData;
	for(auto& item : j.items()) {
		std::string key = item.key();
		dataVariant variant = makeVariantFromJson(item.value());
		internalData.emplace(key, variant);
	}
	return dataVariant(internalData);
}

std::vector<string_view> VariantParser::getKeysFromString(const string_view toParse) {
	std::vector<string_view> keys;
	size_t keyBegin = 0;
	size_t keyEnd = 0;
	while(keyBegin != string_view::npos) {
		keyBegin = toParse.find('{', keyEnd);
		keyEnd = toParse.find('}', keyBegin);
		if(keyBegin != string_view::npos && keyBegin + 1 <= keyEnd - 1) {
			keys.push_back(toParse.substr(keyBegin + 1, keyEnd - keyBegin - 1));
			std::cout << "Key Found: " << keys[keys.size() - 1] << "\n";
		}
	}

	return keys;
}

std::string VariantParser::replaceKeysInString(const string_view baseString, std::vector<string> variables) {
	std::ostringstream parsedString;
	bool writing = true;
	size_t variableIndex = 0;

	for(char c : baseString) {
		if(c == '{') {
			writing = false;
		}
		if(writing) {
			parsedString << c;
		}
		if(c == '}') {
			writing = true;
			parsedString << variables[variableIndex];
			variableIndex++;
		}
	}

	return parsedString.str();
}

std::vector<string_view> VariantParser::splitVariableReference(const string_view toParse) {
	std::vector<string_view> keys;
	size_t lastKey = 0;
	size_t keyEnd = 0;
	while(keyEnd != string_view::npos) {
		keyEnd = toParse.find('.', lastKey);
		if(lastKey <= keyEnd) {
			keys.push_back(toParse.substr(lastKey, keyEnd - lastKey));
			std::cout << "Split Found: " << keys[keys.size() - 1] << "\n";
		}
		lastKey = keyEnd + 1;
	}

	return keys;
}