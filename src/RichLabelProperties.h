#pragma once
#include <string>

enum class Colour {
	Black,
	Red,
	Green,
	Blue,
	Yellow,
	White
};

class RichLabelProperties {
public:
    virtual ~RichLabelProperties() = default;
    virtual Colour getColour() const = 0;
    virtual const std::string& getFontName() const = 0;
    virtual unsigned int getFontSize() const = 0;
};
