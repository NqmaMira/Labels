#include "catch2/catch_all.hpp"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "LabelDecorator.h"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "DecorateTransformation.h"

TEST_CASE("Single transforming decorator trims text", "[decorator]") {
    auto label = std::make_shared<SimpleLabel>("   hello");

    auto decorator = std::make_shared<LabelDecorator>(
        label, std::make_shared<LeftTrimTransformation>());

    REQUIRE(decorator->getText() == "hello");
}

TEST_CASE("Stack multiple transforming decorators in sequence", "[decorator]") {
    auto label = std::make_shared<SimpleLabel>("   hello world  ");

    auto trimDecorator = std::make_shared<LabelDecorator>(
        label, std::make_shared<LeftTrimTransformation>());

    auto capitalizeDecorator = std::make_shared<LabelDecorator>(
        trimDecorator, std::make_shared<CapitalizeTransformation>());

    auto decorateDecorator = std::make_shared<LabelDecorator>(
        capitalizeDecorator, std::make_shared<DecorateTransformation>());

    REQUIRE(decorateDecorator->getText() == "-={ Hello world  }=-");
}

TEST_CASE("LabelDecorator preserves RichLabel properties while transforming text", "[decorator]") {
    auto richLabel = std::make_shared<RichLabel>("   rich text  ", Colour::Blue, "Arial", 12);

    auto decorator = std::make_shared<LabelDecorator>(
        richLabel, std::make_shared<LeftTrimTransformation>());

    REQUIRE(decorator->getText() == "rich text");
    REQUIRE(richLabel->getColour() == Colour::Blue);
    REQUIRE(richLabel->getFontName() == "Arial");
    REQUIRE(richLabel->getFontSize() == 12);
}
