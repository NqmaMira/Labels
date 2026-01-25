#include "RichLabel.h"
#include <utility>

RichLabel::RichLabel(std::string text, Colour colour, std::string fontName, unsigned int fontSize)
	: text(std::move(text)), colour(colour), fontName(std::move(fontName)), fontSize(fontSize) {}

std::string RichLabel::getText() const {
	return text;
}

Colour RichLabel::getColour() const {
	return colour;
}

const std::string& RichLabel::getFontName() const {
	return fontName;
}

unsigned int RichLabel::getFontSize() const {
	return fontSize;
}