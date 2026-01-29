#include "SimpleHelpProvider.h"

SimpleHelpProvider::SimpleHelpProvider(std::string text) : helpText(std::move(text)) { }

std::string SimpleHelpProvider::getHelp() const { 
	return helpText; 
}