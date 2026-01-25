#include "richLabel.h"
#include <utility>

richLabel::richLabel(std::string text, Colour colour, std::string fontName, unsigned int fontSize)
	: text(std::move(text)), colour(colour), fontName(std::move(fontName)), fontSize(fontSize) {}

std::string richLabel::getText() const {
	return text;
}

Colour richLabel::getColour() const {
	return colour;
}

const std::string& richLabel::getFontName() const {
	return fontName;
}

unsigned int richLabel::getFontSize() const {
	return fontSize;
}