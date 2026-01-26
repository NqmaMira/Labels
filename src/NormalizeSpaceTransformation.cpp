#include "NormalizeSpaceTransformation.h"
#include <string>

std::string NormalizeSpaceTransformation::transform(const std::string& input) const {
	std::string result;
	result.reserve(input.size());

	bool prevIsSpace = false;
	for (char c : input) {
		if (c == ' ') {
			if (!prevIsSpace) {
				result.push_back(c);
				prevIsSpace = true;
			}
		}
		else {
			result.push_back(c);
			prevIsSpace = false;
		}
	}
	return result;
}