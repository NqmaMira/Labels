#pragma once
#include "LabelDecorator.h"
#include <vector>
#include <memory>
#include <random>

class RandomTransformDecorator : public LabelDecorator {
public:
	RandomTransformDecorator(std::shared_ptr<Label> label, std::vector<std::shared_ptr<TextTransformation>> transformations);
	std::string getText() const override;
private:
	std::vector<std::shared_ptr<TextTransformation>> transformations;
	mutable std::mt19937 rng{ std::random_device{}() };
};