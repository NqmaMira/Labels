#pragma once
#include "Label.h"
#include "TextTransformation.h"
#include <memory>

class LabelDecorator : public Label {
protected:
    std::shared_ptr<Label> label;
    std::shared_ptr<TextTransformation> transformation;
    static bool isRichLabel(const std::shared_ptr<Label>& label);

public:
    LabelDecorator(std::shared_ptr<Label> label, std::shared_ptr<TextTransformation> transformation);

    const std::shared_ptr<Label>& getLabel() const { return label; }
    virtual std::string getText() const override;
    static std::shared_ptr<Label> create(std::shared_ptr<Label> label, std::shared_ptr<TextTransformation> transformation);
};
