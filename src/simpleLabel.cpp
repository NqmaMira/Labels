#include "simpleLabel.h"

simpleLabel::simpleLabel(std::string text):text(std::move(text)) {}

std::string simpleLabel::getText const{
	return text;
}