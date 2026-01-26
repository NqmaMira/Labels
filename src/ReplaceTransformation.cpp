#include "ReplaceTransformation.h"

ReplaceTransformation::ReplaceTransformation(std::string from, std::string to)
	:from(std::move(from)), to(std::move(to)) {}

std::string ReplaceTransformation::transform(const std::string& input) const {
	if (from.empty()) {
		return input;
	}

	std::string result = input;
	std::size_t pos = 0;

	while ((pos = result.find(from, pos)) != std::string::npos) {
		result.replace(pos, from.length(), to);
		pos += to.length();
	}
	return result;
}