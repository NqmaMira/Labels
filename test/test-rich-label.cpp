#include "catch2/catch_all.hpp"
#include "richLabel.h"

richLabel rLabel{
    "Hello",
    Colour::Green,
    "Arial",
    16
}

TEST_CASE("RichLabel returns correct text") {
    REQUIRE(rLabel.getText() == "Hello");
}

TEST_CASE("RichLabel stores color correctly") {
    REQUIRE(label.getColour() == Colour::Green);
}

TEST_CASE("RichLabel stores font name and size correctly") {
    REQUIRE(label.getFontName() == "Arial");
    REQUIRE(label.getFontSize() == 16);
}

TEST_CASE("RichLabel keeps whitespaces in text") {
    RichLabel rLabel2 (
        "  rich text  ",
        Color::Green,
        "Arial",
        12
    );
    REQUIRE(rLabel2.getText() == "  rich text  ");
}