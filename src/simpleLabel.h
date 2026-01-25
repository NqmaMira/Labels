#pragma once
#include "label.h"

class SimpleLabel :public Label {
private:
	std::string text;
public:
	explicit SimpleLabel(std::string text);
	std::string getText() const override;
};