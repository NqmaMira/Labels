#pragma once
#include "Label.h"
#include "RichLabelProperties.h"
#include <string>

class RichLabel : public Label, public RichLabelProperties {
private:
	std::string text;
	Colour colour;
	std::string fontName;
	unsigned int fontSize;

public:
	RichLabel(std::string text, Colour colour, std::string fontName, unsigned int fontSize);
	std::string getText() const override;
	Colour getColour() const override;
	const std::string& getFontName() const override;
	unsigned int getFontSize() const override;
};