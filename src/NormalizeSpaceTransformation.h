#pragma once
#include "TextTransformation.h"
#include <string>

class NormalizeSpaceTransformation : public TextTransformation {
public:
	std::string transform(const std::string & input) const override;
};