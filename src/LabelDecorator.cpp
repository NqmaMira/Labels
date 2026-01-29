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
    if (!transformation) {
        return label->getText();
    }
    return transformation->transform(label->getText());
}

std::shared_ptr<Label> LabelDecorator::create(std::shared_ptr<Label> label, std::shared_ptr<TextTransformation> transformation) {
    if (isRichLabel(label)) {
        return std::make_shared<RichLabelDecorator>(label, transformation);
    }
    return std::make_shared<LabelDecorator>(label, transformation);
}

std::shared_ptr<Label> LabelDecorator::remove(std::shared_ptr<Label> head, std::shared_ptr<LabelDecorator> toRemove) {
    if (!head || !toRemove) {
        return head;
    }

    if (head == toRemove) {
        return toRemove->getLabel();
    }

    auto decorator = std::dynamic_pointer_cast<LabelDecorator>(head);
    if (decorator) {
        decorator->label = remove(decorator->getLabel(), toRemove);
        return decorator;
    }
    return head;
}