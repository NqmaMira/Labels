#include "CensorTransformation.h"
#include <string>

CensorTransformation::CensorTransformation(std::string word)
	: word(std::move(word)), mask(this->word.size(), '*') {}

std::string CensorTransformation::transform(const std::string& input) const {
	if (word.empty() || word.size() > input.size()) {
		return input;
	}

	std::string result = input;
	std::size_t pos = 0;

	while ((pos = result.find(word, pos)) != std::string::npos) {
		result.replace(pos, word.size(), mask);
		pos += mask.size();
	}
	return result;
}