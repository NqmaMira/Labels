#pragma once
#include "TextTransformation.h"
#include <vector>
#include <memory>

class CompositeTransformation : public TextTransformation {
private:
    std::vector<std::shared_ptr<TextTransformation>> transformations;

public:
    CompositeTransformation() = default;

    void add(std::shared_ptr<TextTransformation> transformation);

    std::string transform(const std::string& input) const override;
};