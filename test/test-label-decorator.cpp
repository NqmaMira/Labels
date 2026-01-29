#include "catch2/catch_all.hpp"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "LabelDecorator.h"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "DecorateTransformation.h"
#include <RandomTransformDecorator.h>
#include <CensorTransformation.h>
#include <CompositeTransformation.h>

TEST_CASE("LabelDecorator applies transformation to SimpleLabel without making it rich", "[decorator]") {
    auto simple = std::make_shared<SimpleLabel>("   hello");
    auto decoratedSimple = LabelDecorator::create(simple, std::make_shared<LeftTrimTransformation>());

    REQUIRE(decoratedSimple->getText() == "hello");
    REQUIRE(dynamic_cast<RichLabelProperties*>(decoratedSimple.get()) == nullptr);
}

TEST_CASE("LabelDecorator applies transformation to RichLabel and preserves rich properties", "[decorator]") {
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

TEST_CASE("Stacked LabelDecorators preserve RichLabelProperties", "[decorator]") {
    auto rich = std::make_shared<RichLabel>(" text ", Colour::Red, "Arial", 14);

    auto d1 = LabelDecorator::create(rich, std::make_shared<LeftTrimTransformation>());
    auto d2 = LabelDecorator::create(d1, std::make_shared<CapitalizeTransformation>());

    auto richView = dynamic_cast<RichLabelProperties*>(d2.get());
    REQUIRE(richView != nullptr);
    REQUIRE(richView->getFontName() == "Arial");
}

TEST_CASE("RandomTransformDecorator applies all transformations probabilistically", "[decorator][random]") {
    auto label = std::make_shared<SimpleLabel>("   hello");

    auto randomDecorator = std::make_shared<RandomTransformDecorator>(
        label,
        std::vector<std::shared_ptr<TextTransformation>>{
        std::make_shared<LeftTrimTransformation>(),
            std::make_shared<CensorTransformation>("hello"),
            std::make_shared<DecorateTransformation>()
    });

    bool seenTrim = false, seenCensor = false, seenDecorate = false;
    const int maxIterations = 500;

    for (int i = 0; i < maxIterations; ++i) {
        auto output = randomDecorator->getText();

        if (!seenTrim && !output.empty() && output.front() != ' ') seenTrim = true;
        if (!seenCensor && output.find("*****") != std::string::npos) seenCensor = true;
        if (!seenDecorate && output.find("-={") != std::string::npos) seenDecorate = true;

        if (seenTrim && seenCensor && seenDecorate) break;
    }

    REQUIRE(seenTrim);
    REQUIRE(seenCensor);
    REQUIRE(seenDecorate);
}

TEST_CASE("RandomTransformDecorator preserves RichLabel properties", "[decorator][random]") {
    auto rich = std::make_shared<RichLabel>(" text ", Colour::Red, "Arial", 14);

    auto randomDecorator = std::make_shared<RandomTransformDecorator>(
        rich,
        std::vector<std::shared_ptr<TextTransformation>> {
            std::make_shared<LeftTrimTransformation>(), std::make_shared<CapitalizeTransformation>()
        }
    );

    auto richView = dynamic_cast<RichLabelProperties*>(randomDecorator->getLabel().get());
    REQUIRE(richView != nullptr);
    REQUIRE(richView->getFontName() == "Arial");
    REQUIRE(richView->getColour() == Colour::Red);
}

TEST_CASE("LabelDecorator works correctly with CompositeTransformation", "[decorator][composite]") {
    auto composite = std::make_shared<CompositeTransformation>();
    composite->add(std::make_shared<CapitalizeTransformation>());
    composite->add(std::make_shared<DecorateTransformation>());

    auto label = std::make_shared<SimpleLabel>("hello");
    auto decorated = std::make_shared<LabelDecorator>(label, composite);

    REQUIRE(decorated->getText() == "-={ Hello }=-");
}

TEST_CASE("CompositeTransformation can be stacked with other decorators", "[decorator][composite]") {
    auto composite = std::make_shared<CompositeTransformation>();
    composite->add(std::make_shared<CapitalizeTransformation>());
    composite->add(std::make_shared<DecorateTransformation>());

    auto label = std::make_shared<SimpleLabel>("   hello");

    auto trim = LabelDecorator::create(label, std::make_shared<LeftTrimTransformation>());
    auto compositeDecorator = LabelDecorator::create(trim, composite);

    REQUIRE(compositeDecorator->getText() == "-={ Hello }=-");
}

TEST_CASE("CompositeTransformation preserves RichLabel properties when used in LabelDecorator", "[decorator][composite]") {
    auto composite = std::make_shared<CompositeTransformation>();
    composite->add(std::make_shared<CapitalizeTransformation>());
    composite->add(std::make_shared<DecorateTransformation>());

    auto rich = std::make_shared<RichLabel>("hello", Colour::Blue, "Arial", 12);
    auto decorated = LabelDecorator::create(rich, composite);

    REQUIRE(decorated->getText() == "-={ Hello }=-");

    auto richView = dynamic_cast<RichLabelProperties*>(decorated.get());
    REQUIRE(richView != nullptr);
    REQUIRE(richView->getColour() == Colour::Blue);
    REQUIRE(richView->getFontName() == "Arial");
    REQUIRE(richView->getFontSize() == 12);
}

TEST_CASE("Removing a decorator from a chain works as expected", "[decorator][remove]") {
    auto base = std::make_shared<SimpleLabel>("hello");
    auto cap = std::make_shared<LabelDecorator>(base, std::make_shared<CapitalizeTransformation>());
    auto dec = std::make_shared<LabelDecorator>(cap, std::make_shared<DecorateTransformation>());

    REQUIRE(dec->getText() == "-={ Hello }=-");

    SECTION("Can remove the outer decorator") {
        auto newHead = LabelDecorator::remove(dec, dec);
        REQUIRE(newHead->getText() == "Hello");
    }

    SECTION("Can remove the inner decorator") {
        auto newHead = LabelDecorator::remove(dec, cap);
        REQUIRE(newHead->getText() == "-={ hello }=-");
    }
}