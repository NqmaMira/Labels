#include "LabelDecorator.h"
#include "RichLabelDecorator.h"
#include "RichLabelProperties.h"
#include <cassert>

bool LabelDecorator::isRichLabel(const std::shared_ptr<Label>& lbl) {
    if (dynamic_cast<RichLabelProperties*>(lbl.get())) return true;

    auto decorator = dynamic_cast<LabelDecorator*>(lbl.get());
    if (decorator) {
		return isRichLabel(decorator->label);
    }

    return false;
}

LabelDecorator::LabelDecorator(
    std::shared_ptr<Label> label,
    std::shared_ptr<TextTransformation> transformation)
    : label(std::move(label)), transformation(std::move(transformation)) {}

std::string LabelDecorator::getText() const {
    return transformation->transform(label->getText());
}

std::shared_ptr<Label> LabelDecorator::create(std::shared_ptr<Label> label, std::shared_ptr<TextTransformation> transformation) {
    if (isRichLabel(label)) {
        return std::make_shared<RichLabelDecorator>(label, transformation);
    }
    return std::make_shared<LabelDecorator>(label, transformation);
}
