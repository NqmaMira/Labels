#pragma once
#include "Label.h"
#include "TextTransformation.h"
#include <memory>

class LabelDecorator : public Label {
private:
    std::shared_ptr<Label> label;
    std::shared_ptr<TextTransformation> transformation;

public:
    LabelDecorator(std::shared_ptr<Label> label,
        std::shared_ptr<TextTransformation> transformation);

    std::string getText() const override;
};
