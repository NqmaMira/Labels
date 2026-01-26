#include "LabelDecorator.h"

LabelDecorator::LabelDecorator(
    std::shared_ptr<Label> label,
    std::shared_ptr<TextTransformation> transformation)
    : label(std::move(label)), transformation(std::move(transformation)) {}

std::string LabelDecorator::getText() const {
    return transformation->transform(label->getText());
}
