#pragma once
#include "label.h"

class simpleLabel :public label {
private:
	std::string text;
public:
	explicit simpleLabel(std::string text);
	std::string getText() const override;
};