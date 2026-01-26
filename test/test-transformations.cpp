#include "catch2/catch_all.hpp"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "RightTrimTransformation.h"
#include "NormalizeSpaceTransformation.h"
#include "DecorateTransformation.h"
#include "CensorTransformation.h"
#include "ReplaceTransformation.h"

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

TEST_CASE("LeftTrimTransformation removes leading tabs", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("\t\tabc") == "abc");
}

TEST_CASE("LeftTrimTransformation removes leading newlines", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("\n\nabc") == "abc");
}

TEST_CASE("LeftTrimTransformation removes leading carriage returns", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("\r\rabc") == "abc");
}

TEST_CASE("LeftTrimTransformation removes mixed leading whitespace characters", "[leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform(" \t\n\r abc") == "abc");
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

TEST_CASE("RightTrimTransformation removes trailing tabs", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc\t\t") == "abc");
}

TEST_CASE("RightTrimTransformation removes trailing newlines", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc\n\n") == "abc");
}

TEST_CASE("RightTrimTransformation removes trailing carriage returns", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc\r\r") == "abc");
}

TEST_CASE("RightTrimTransformation removes mixed trailing whitespace characters", "[rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc \t\n\r ") == "abc");
}

TEST_CASE("NormalizeSpaceTransformation collapses multiple inner spaces into one", "[normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("some   text") == "some text");
}

TEST_CASE("NormalizeSpaceTransformation preserves leading and trailing spaces while normalizing inner spaces", "[normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform(" some    text ") == " some text ");
}

TEST_CASE("NormalizeSpaceTransformation leaves string without extra spaces unchanged", "[normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("noextra") == "noextra");
}

TEST_CASE("NormalizeSpaceTransformation reduces all-spaces string to a single space", "[normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("   ") == " ");
}

TEST_CASE("NormalizeSpaceTransformation handles empty string", "[normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("") == "");
}

TEST_CASE("DecorateTransformation wraps non-empty text", "[decorate]") {
	DecorateTransformation t;
	REQUIRE(t.transform("abc") == "-={ abc }=-");
}

TEST_CASE("DecorateTransformation wraps empty string", "[decorate]") {
	DecorateTransformation t;
	REQUIRE(t.transform("") == "-={  }=-");
}

TEST_CASE("DecorateTransformation preserves inner spaces while decorating", "[decorate]") {
	DecorateTransformation t;
	REQUIRE(t.transform(" text ") == "-={  text  }=-");
}

TEST_CASE("CensorTransformation censors a single occurrence", "[censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform(" abc def") == " *** def");
}

TEST_CASE("CensorTransformation censors multiple occurrences", "[censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform(" abc def abcdef") == " *** def ***def");
}

TEST_CASE("CensorTransformation censors overlapping occurrences", "[censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform("abcabc") == "******");
}

TEST_CASE("CensorTransformation leaves text unchanged when no match is found", "[censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform("no match") == "no match");
}

TEST_CASE("CensorTransformation with empty censored word does nothing", "[censor]") {
	CensorTransformation t("");
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("ReplaceTransformation replaces a single occurrence", "[replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform(" abc def") == " d def");
}

TEST_CASE("ReplaceTransformation replaces multiple occurrences", "[replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform(" abc abcdef") == " d ddef");
}

TEST_CASE("ReplaceTransformation replaces overlapping occurrences", "[replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform("abcabc") == "dd");
}

TEST_CASE("ReplaceTransformation leaves text unchanged when no match is found", "[replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform("no match") == "no match");
}

TEST_CASE("ReplaceTransformation with empty source string does nothing", "[replace]") {
	ReplaceTransformation t("", "x");
	REQUIRE(t.transform("abc") == "abc");
}
