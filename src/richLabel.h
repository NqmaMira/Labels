#pragma once
#include "label.h"
#include <string>

enum class Colour {
	Black,
	Red,
	Green,
	Blue,
	Yellow,
	White
};

class richLabel :public label {
private:
	std::string text;
	Colour colour;
	std::string fontName;
	unsigned int fontSize;

public:
	richLabel(std::string text, Colour colour, std::string fontName, unsigned int fontSize);
	std::string getText() const override;
	Colour getColour() const;
	const std::string& getFontName() const;
	unsigned int getFontSize() const;
};