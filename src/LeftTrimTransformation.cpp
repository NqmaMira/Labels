#include "LeftTrimTransformation.h"
#include <string>

std::string LeftTrimTransformation::transform(const std::string& input) const {
	std::string result = input;
	result.erase(0, result.find_first_not_of(" \t\n\r"));
	return result;
}