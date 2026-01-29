#include "catch2/catch_all.hpp"
#include "RichLabel.h"

TEST_CASE("RichLabel returns correct text", "[label]") {
    RichLabel rLabel(
        "Hello",
        Colour::Red,
        "Arial",
        18
    );
    REQUIRE(rLabel.getText() == "Hello");
}

TEST_CASE("RichLabel stores color correctly", "[label]") {
    RichLabel rLabel(
        "Hello",
        Colour::Green,
        "Arial",
        18
    );
    REQUIRE(rLabel.getColour() == Colour::Green);
}

TEST_CASE("RichLabel stores font name and size correctly", "[label]") {
    RichLabel rLabel(
        "Hello",
        Colour::Green,
        "Times New Roman",
        16
    );
    REQUIRE(rLabel.getFontName() == "Times New Roman");
    REQUIRE(rLabel.getFontSize() == 16);
}

TEST_CASE("RichLabel keeps whitespaces in text", "[label]") {
    RichLabel rLabel (
        "  rich text  ",
        Colour::Green,
        "Arial",
        12
    );
    REQUIRE(rLabel.getText() == "  rich text  ");
}