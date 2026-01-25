#pragma once
#include "TextTransformation.h"
#include <string>

class LeftTrimTransformation : public TextTransformation {
public:
	std::string transform(const std::string& input) const override;
};