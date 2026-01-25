#pragma once
#include <string>

class TextTransformation {
public:
	virtual ~TextTransformation() = default;
	virtual std::string transform(const std::string& input) const = 0;
};