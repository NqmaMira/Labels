#pragma once
#include "TextTransformation.h"
#include <string>

class CensorTransformation :public TextTransformation {
private:
	std::string word;
	std::string mask;
public:
	explicit CensorTransformation(std::string word);
	std::string transform(const std::string& input) const override;
};