#include "catch2/catch_all.hpp"
#include "RichLabel.h"
#include <CustomLabel.h>
#include <SimpleHelpProvider.h>
#include <CapitalizeTransformation.h>
#include <LabelDecorator.h>
#include <HelpLabel.h>
#include <SimpleLabel.h>

TEST_CASE("RichLabel returns correct text", "[label][rich]") {
    RichLabel rLabel(
        "Hello",
        Colour::Red,
        "Arial",
        18
    );
    REQUIRE(rLabel.getText() == "Hello");
}

TEST_CASE("RichLabel stores color correctly", "[label][rich]") {
    RichLabel rLabel(
        "Hello",
        Colour::Green,
        "Arial",
        18
    );
    REQUIRE(rLabel.getColour() == Colour::Green);
}

TEST_CASE("RichLabel stores font name and size correctly", "[label][rich]") {
    RichLabel rLabel(
        "Hello",
        Colour::Green,
        "Times New Roman",
        16
    );
    REQUIRE(rLabel.getFontName() == "Times New Roman");
    REQUIRE(rLabel.getFontSize() == 16);
}

TEST_CASE("RichLabel keeps whitespaces in text", "[label][rich]") {
    RichLabel rLabel (
        "  rich text  ",
        Colour::Green,
        "Arial",
        12
    );
    REQUIRE(rLabel.getText() == "  rich text  ");
}

TEST_CASE("CustomLabel has lazy loading and timeout logic", "[label][custom]") {
    std::stringstream mockInput;
    std::stringstream mockOutput;

    auto* oldCin = std::cin.rdbuf(mockInput.rdbuf());
    auto* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    SECTION("CustomLabel fetches text on first call") {
        mockInput << "First Input\n";
        CustomLabel proxy(3);

        std::string result = proxy.getText();
        REQUIRE(result == "First Input");
        REQUIRE(mockOutput.str().find("Enter label text:") != std::string::npos);
    }

    SECTION("CustomLabel caches text and does not re-prompt before timeout") {
        mockInput << "First Input\n";
        CustomLabel proxy(2);
        proxy.getText();
        mockOutput.str("");

        std::string result = proxy.getText();
        REQUIRE(result == "First Input");
        REQUIRE(mockOutput.str().empty());
    }

    SECTION("CustomLabel re-prompts after timeout is reached") {
        mockInput << "First Input\nSecond Input\n";
        CustomLabel proxy(2);
        proxy.getText();
        proxy.getText();
        mockOutput.str("");

        std::string result = proxy.getText();
        REQUIRE(result == "Second Input");
        REQUIRE(mockOutput.str().find("Enter label text:") != std::string::npos);
    }

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
}

TEST_CASE("HelpLabel factory provides help text", "[label][help]") {
    auto simple = std::make_shared<SimpleLabel>("Some Text");
    auto help = std::make_shared<SimpleHelpProvider>("This is helpful");
    auto wrapped = HelpLabel::create(simple, help);

    auto asHelp = std::dynamic_pointer_cast<HelpLabel>(wrapped);
    REQUIRE(asHelp != nullptr);
    REQUIRE(asHelp->getHelpText() == "This is helpful");
}

TEST_CASE("HelpLabel factory preserves rich properties", "[label][help]") {
    auto rich = std::make_shared<RichLabel>("Rich Text", Colour::Red, "Consolas", 10);
    auto help = std::make_shared<SimpleHelpProvider>("This is helpful");
    auto wrapped = HelpLabel::create(rich, help);

    auto asHelp = std::dynamic_pointer_cast<HelpLabel>(wrapped);
    REQUIRE(asHelp != nullptr);
    REQUIRE(asHelp->getHelpText() == "This is helpful");

    auto asRich = std::dynamic_pointer_cast<RichLabelProperties>(wrapped);
    REQUIRE(asRich != nullptr);
    REQUIRE(asRich->getColour() == Colour::Red);
}