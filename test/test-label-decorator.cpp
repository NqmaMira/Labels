#include "catch2/catch_all.hpp"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "LabelDecorator.h"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "DecorateTransformation.h"

TEST_CASE("LabelDecorator applies transformation to SimpleLabel without making it rich",
    "[decorator]") {
    auto simple = std::make_shared<SimpleLabel>("   hello");
    auto decoratedSimple = LabelDecorator::create(simple, std::make_shared<LeftTrimTransformation>());

    REQUIRE(decoratedSimple->getText() == "hello");
    REQUIRE(dynamic_cast<RichLabelProperties*>(decoratedSimple.get()) == nullptr);
}

TEST_CASE("LabelDecorator applies transformation to RichLabel and preserves rich properties",
    "[decorator]") {
    auto rich = std::make_shared<RichLabel>("   rich text  ", Colour::Blue, "Arial", 12);
    auto decoratedRich = LabelDecorator::create(rich, std::make_shared<LeftTrimTransformation>());

    REQUIRE(decoratedRich->getText() == "rich text  ");

    auto richView = dynamic_cast<RichLabelProperties*>(decoratedRich.get());
    REQUIRE(richView != nullptr);
    REQUIRE(richView->getColour() == Colour::Blue);
    REQUIRE(richView->getFontName() == "Arial");
    REQUIRE(richView->getFontSize() == 12);
}

TEST_CASE("LabelDecorator supports stacking multiple transformations correctly", "[decorator]") {
    auto label = std::make_shared<SimpleLabel>("   hello world  ");

    auto trimDecorator = LabelDecorator::create(label, std::make_shared<LeftTrimTransformation>());
    auto capitalizeDecorator = LabelDecorator::create(trimDecorator, std::make_shared<CapitalizeTransformation>());
    auto decorateDecorator = LabelDecorator::create(capitalizeDecorator, std::make_shared<DecorateTransformation>());

    REQUIRE(decorateDecorator->getText() == "-={ Hello world   }=-");
}

TEST_CASE("Stacked LabelDecorators preserve RichLabelProperties", "[decorator][rich][stacking]") {
    auto rich = std::make_shared<RichLabel>(" text ", Colour::Red, "Arial", 14);

    auto d1 = LabelDecorator::create(rich, std::make_shared<LeftTrimTransformation>());
    auto d2 = LabelDecorator::create(d1, std::make_shared<CapitalizeTransformation>());

    auto richView = dynamic_cast<RichLabelProperties*>(d2.get());
    REQUIRE(richView != nullptr);
    REQUIRE(richView->getFontName() == "Arial");
}