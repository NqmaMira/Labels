#pragma once
#include "HelpLabel.h"
#include "RichLabelProperties.h"

class RichHelpLabel : public HelpLabel, public RichLabelProperties {
public:
    using HelpLabel::HelpLabel;

    Colour getColour() const override;
    const std::string& getFontName() const override;
    unsigned int getFontSize() const override;
};