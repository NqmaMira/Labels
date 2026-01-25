#include "SimpleLabel.h"

SimpleLabel::SimpleLabel(std::string text):text(std::move(text)) {}

std::string SimpleLabel::getText() const{
	return text;
}