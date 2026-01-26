#include "RichLabelDecorator.h"

const RichLabelProperties* RichLabelDecorator::findRichLabel(const Label* lbl) const {
    if (!lbl) return nullptr;

    if (auto rich = dynamic_cast<const RichLabelProperties*>(lbl))
        return rich;

    if (auto decorator = dynamic_cast<const LabelDecorator*>(lbl))
        return findRichLabel(decorator->getLabel().get());

    return nullptr;
}

RichLabelDecorator::RichLabelDecorator(std::shared_ptr<Label> label, std::shared_ptr<TextTransformation> transformation)
    : LabelDecorator(std::move(label), std::move(transformation)) { }

Colour RichLabelDecorator::getColour() const {
    auto rich = dynamic_cast<RichLabelProperties*>(label.get());
    assert(rich); 
    return rich->getColour();
}

const std::string& RichLabelDecorator::getFontName() const {
    auto rich = dynamic_cast<RichLabelProperties*>(label.get());
    assert(rich);
    return rich->getFontName();
}

unsigned int RichLabelDecorator::getFontSize() const {
    auto rich = dynamic_cast<RichLabelProperties*>(label.get());
    assert(rich);
    return rich->getFontSize();
}