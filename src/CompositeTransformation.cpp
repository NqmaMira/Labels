#include "CompositeTransformation.h"
#include <utility>

void CompositeTransformation::add(std::shared_ptr<TextTransformation> transformation) {
    if (transformation) {
        transformations.push_back(std::move(transformation));
    }
}

std::string CompositeTransformation::transform(const std::string& input) const {
    std::string result = input;
    for (const auto& t : transformations) {
        result = t->transform(result);
    }
    return result;
}