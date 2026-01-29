#include "RichHelpLabel.h"
#include "RichLabelProperties.h"
#include <cassert>

static const RichLabelProperties* findRichLabel(const Label* lbl) {
    if (!lbl) return nullptr;
    if (auto rich = dynamic_cast<const RichLabelProperties*>(lbl)) return rich;
    if (auto decorator = dynamic_cast<const LabelDecorator*>(lbl))
        return findRichLabel(decorator->getLabel().get());
    return nullptr;
}

Colour RichHelpLabel::getColour() const {
    auto rich = findRichLabel(label.get());
    assert(rich);
    return rich->getColour();
}

const std::string& RichHelpLabel::getFontName() const {
    auto rich = findRichLabel(label.get());
    assert(rich);
    return rich->getFontName();
}

unsigned int RichHelpLabel::getFontSize() const {
    auto rich = findRichLabel(label.get());
    assert(rich);
    return rich->getFontSize();
}