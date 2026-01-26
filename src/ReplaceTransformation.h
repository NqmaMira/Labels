#pragma once
#include "TextTransformation.h"
#include <string>

class ReplaceTransformation :public TextTransformation {
private:
	std::string from;
	std::string to;

public:
	ReplaceTransformation(std::string from, std::string to);
	std::string transform(const std::string& input) const override;
};