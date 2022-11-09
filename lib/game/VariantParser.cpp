#include <VariantParser.h>

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
	//this is the complex case - could be vector or map, 
	//and either needs the underlying variants built as well
		//data = dataVariant(j.get<float>());
		break;

	default:
		break;
	}

	return data;
}