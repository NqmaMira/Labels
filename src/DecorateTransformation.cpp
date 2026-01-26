#include "DecorateTransformation.h"

std::string DecorateTransformation::transform(const std::string& input) const {
	return "-={ " + input + " }=-";
}