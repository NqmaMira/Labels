#include "catch2/catch_all.hpp"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "RightTrimTransformation.h"

TEST_CASE("CapitalizeTransformation capitalizes first letter when it is lowercase", "[capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("capitalize me") == "Capitalize me");
}

TEST_CASE("CapitalizeTransformation leaves capitalized string unchanged", "[capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("Some text") == "Some text");
}

TEST_CASE("CapitalizeTransformation does not modify string starting with digit", "[capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("1asd") == "1asd");
}

TEST_CASE("CapitalizeTransformation does not modify string starting with symbol", "[capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("@symbol") == "@symbol");
}

TEST_CASE("CapitalizeTransformation handles empty string", "[capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("") == "");
}



TEST_CASE("LeftTrimTransformation removes leading spaces", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("   abc") == "abc");
}

TEST_CASE("LeftTrimTransformation preserves trailing spaces", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform(" abc  ") == "abc  ");
}

TEST_CASE("LeftTrimTransformation leaves string without leading spaces unchanged", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("LeftTrimTransformation turns all-spaces string into empty string", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("   ") == "");
}

TEST_CASE("LeftTrimTransformation handles empty string", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("") == "");
}


TEST_CASE("RightTrimTransformation removes trailing spaces", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc   ") == "abc");
}

TEST_CASE("RightTrimTransformation preserves leading spaces", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("  abc  ") == "  abc");
}

TEST_CASE("RightTrimTransformation leaves string without trailing spaces unchanged", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("RightTrimTransformation turns all-spaces string into empty string", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("   ") == "");
}

TEST_CASE("RightTrimTransformation handles empty string", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("") == "");
}