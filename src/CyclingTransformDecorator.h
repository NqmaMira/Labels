#pragma once
#include "LabelDecorator.h"
#include <vector>
#include <memory>

class CyclingTransformDecorator : public LabelDecorator {
private:
    std::vector<std::shared_ptr<TextTransformation>> transformations;
    mutable std::size_t currentIndex;

public:
    CyclingTransformDecorator(std::shared_ptr<Label> label,
        std::vector<std::shared_ptr<TextTransformation>> transformations);

    std::string getText() const override;
};