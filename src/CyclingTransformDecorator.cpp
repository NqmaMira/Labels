#include "CyclingTransformDecorator.h"
#include <utility>

CyclingTransformDecorator::CyclingTransformDecorator(std::shared_ptr<Label> label,
    std::vector<std::shared_ptr<TextTransformation>> transformations)
    : LabelDecorator(std::move(label), nullptr), transformations(std::move(transformations)), currentIndex(0) { }

std::string CyclingTransformDecorator::getText() const {
    if (transformations.empty()) {
        return label->getText();
    }

    std::string result = transformations[currentIndex]->transform(label->getText());
    currentIndex = (currentIndex + 1) % transformations.size();
    return result;
}