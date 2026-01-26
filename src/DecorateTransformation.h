#pragma once
#include "TextTransformation.h"

class DecorateTransformation : public TextTransformation {
public:
	std::string transform(const std::string& input) const override;
};