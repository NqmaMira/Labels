#include "RichHelpLabel.h"
#include "RichLabelProperties.h"

Colour RichHelpLabel::getColour() const {
    return dynamic_cast<RichLabelProperties*>(label.get())->getColour();
}

const std::string& RichHelpLabel::getFontName() const {
    return dynamic_cast<RichLabelProperties*>(label.get())->getFontName();
}

unsigned int RichHelpLabel::getFontSize() const {
    return dynamic_cast<RichLabelProperties*>(label.get())->getFontSize();
}