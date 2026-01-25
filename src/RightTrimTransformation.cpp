#include "RightTrimTransformation.h"
#include <string>

std::string RightTrimTransformation::transform(const std::string& input) const {
	std::string result = input;
	result.erase(result.find_last_not_of(' ') + 1);
	return result;
}