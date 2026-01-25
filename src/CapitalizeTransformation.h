#pragma once
#include "TextTransformation.h"
#include <algorithm>

class CapitalizeTransformation : public TextTransformation {
public:
	std::string transform(const std::string& input) const override;
};