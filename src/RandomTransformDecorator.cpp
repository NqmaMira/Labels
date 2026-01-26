#include "RandomTransformDecorator.h"
#include <cassert>
#include <random>

RandomTransformDecorator::RandomTransformDecorator(std::shared_ptr<Label> label, std::vector<std::shared_ptr<TextTransformation>> transformations)
	: LabelDecorator(label, nullptr), transformations(std::move(transformations)) {
	assert(label);
	assert(!this->transformations.empty());
}

std::string RandomTransformDecorator::getText() const {
	assert(label);
	assert(!transformations.empty());

	std::uniform_int_distribution<std::size_t> dist(0, transformations.size() - 1);
	auto chosen = transformations[dist(rng)];
	return chosen->transform(label->getText());
}