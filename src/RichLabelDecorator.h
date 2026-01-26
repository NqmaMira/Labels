#pragma once
#include "LabelDecorator.h"
#include "RichLabelProperties.h"
#include <memory>
#include <cassert>

class RichLabelDecorator final : public LabelDecorator, public RichLabelProperties {
public:
    RichLabelDecorator(std::shared_ptr<Label> label, std::shared_ptr<TextTransformation> transformation);

    Colour getColour() const override;
    const std::string& getFontName() const override;
    unsigned int getFontSize() const override;
private:
    const RichLabelProperties* findRichLabel(const Label* lbl) const;
};