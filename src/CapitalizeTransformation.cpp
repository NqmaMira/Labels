#include "CapitalizeTransformation.h"
#include <cctype>
#include <string>

std::string CapitalizeTransformation::transform(const std::string& input) const {
	if (input.empty()) {
		return input;
	}
	std::string result = input;
	if (std::islower(static_cast<unsigned char>(input[0]))) {
		result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
	}
	return result;
}