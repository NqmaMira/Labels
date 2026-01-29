#include "catch2/catch_all.hpp"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "RightTrimTransformation.h"
#include "NormalizeSpaceTransformation.h"
#include "DecorateTransformation.h"
#include "CensorTransformation.h"
#include "ReplaceTransformation.h"
#include <CompositeTransformation.h>
#include <CensorFactory.h>

TEST_CASE("CapitalizeTransformation capitalizes first letter when it is lowercase", "[transformation][capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("capitalize me") == "Capitalize me");
}

TEST_CASE("CapitalizeTransformation leaves capitalized string unchanged", "[transformation][capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("Some text") == "Some text");
}

TEST_CASE("CapitalizeTransformation does not modify string starting with digit", "[transformation][capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("1asd") == "1asd");
}

TEST_CASE("CapitalizeTransformation does not modify string starting with symbol", "[transformation][capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("@symbol") == "@symbol");
}

TEST_CASE("CapitalizeTransformation handles empty string", "[transformation][capitalize]") {
	CapitalizeTransformation t;
	REQUIRE(t.transform("") == "");
}

TEST_CASE("LeftTrimTransformation removes leading spaces", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("   abc") == "abc");
}

TEST_CASE("LeftTrimTransformation preserves trailing spaces", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform(" abc  ") == "abc  ");
}

TEST_CASE("LeftTrimTransformation leaves string without leading spaces unchanged", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("LeftTrimTransformation turns all-spaces string into empty string", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("   ") == "");
}

TEST_CASE("LeftTrimTransformation handles empty string", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("") == "");
}

TEST_CASE("LeftTrimTransformation removes leading tabs", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("\t\tabc") == "abc");
}

TEST_CASE("LeftTrimTransformation removes leading newlines", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("\n\nabc") == "abc");
}

TEST_CASE("LeftTrimTransformation removes leading carriage returns", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform("\r\rabc") == "abc");
}

TEST_CASE("LeftTrimTransformation removes mixed leading whitespace characters", "[transformation][leftTrim]") {
	LeftTrimTransformation t;
	REQUIRE(t.transform(" \t\n\r abc") == "abc");
}

TEST_CASE("RightTrimTransformation removes trailing spaces", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc   ") == "abc");
}

TEST_CASE("RightTrimTransformation preserves leading spaces", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("  abc  ") == "  abc");
}

TEST_CASE("RightTrimTransformation leaves string without trailing spaces unchanged", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("RightTrimTransformation turns all-spaces string into empty string", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("   ") == "");
}

TEST_CASE("RightTrimTransformation handles empty string", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("") == "");
}

TEST_CASE("RightTrimTransformation removes trailing tabs", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc\t\t") == "abc");
}

TEST_CASE("RightTrimTransformation removes trailing newlines", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc\n\n") == "abc");
}

TEST_CASE("RightTrimTransformation removes trailing carriage returns", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc\r\r") == "abc");
}

TEST_CASE("RightTrimTransformation removes mixed trailing whitespace characters", "[transformation][rightTrim]") {
	RightTrimTransformation t;
	REQUIRE(t.transform("abc \t\n\r ") == "abc");
}

TEST_CASE("NormalizeSpaceTransformation collapses multiple inner spaces into one", "[transformation][normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("some   text") == "some text");
}

TEST_CASE("NormalizeSpaceTransformation preserves leading and trailing spaces while normalizing inner spaces", "[transformation][normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform(" some    text ") == " some text ");
}

TEST_CASE("NormalizeSpaceTransformation leaves string without extra spaces unchanged", "[transformation][normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("noextra") == "noextra");
}

TEST_CASE("NormalizeSpaceTransformation reduces all-spaces string to a single space", "[transformation][normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("   ") == " ");
}

TEST_CASE("NormalizeSpaceTransformation handles empty string", "[transformation][normalizeSpace]") {
	NormalizeSpaceTransformation t;
	REQUIRE(t.transform("") == "");
}

TEST_CASE("DecorateTransformation wraps non-empty text", "[transformation][decorate]") {
	DecorateTransformation t;
	REQUIRE(t.transform("abc") == "-={ abc }=-");
}

TEST_CASE("DecorateTransformation wraps empty string", "[transformation][decorate]") {
	DecorateTransformation t;
	REQUIRE(t.transform("") == "-={  }=-");
}

TEST_CASE("DecorateTransformation preserves inner spaces while decorating", "[transformation][decorate]") {
	DecorateTransformation t;
	REQUIRE(t.transform(" text ") == "-={  text  }=-");
}

TEST_CASE("CensorTransformation censors a single occurrence", "[transformation][censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform(" abc def") == " *** def");
}

TEST_CASE("CensorTransformation censors multiple occurrences", "[transformation][censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform(" abc def abcdef") == " *** def ***def");
}

TEST_CASE("CensorTransformation censors overlapping occurrences", "[transformation][censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform("abcabc") == "******");
}

TEST_CASE("CensorTransformation leaves text unchanged when no match is found", "[transformation][censor]") {
	CensorTransformation t("abc");
	REQUIRE(t.transform("no match") == "no match");
}

TEST_CASE("CensorTransformation with empty censored word does nothing", "[transformation][censor]") {
	CensorTransformation t("");
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("ReplaceTransformation replaces a single occurrence", "[transformation][replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform(" abc def") == " d def");
}

TEST_CASE("ReplaceTransformation replaces multiple occurrences", "[transformation][replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform(" abc abcdef") == " d ddef");
}

TEST_CASE("ReplaceTransformation replaces overlapping occurrences", "[transformation][replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform("abcabc") == "dd");
}

TEST_CASE("ReplaceTransformation leaves text unchanged when no match is found", "[transformation][replace]") {
	ReplaceTransformation t("abc", "d");
	REQUIRE(t.transform("no match") == "no match");
}

TEST_CASE("ReplaceTransformation with empty source string does nothing", "[transformation][replace]") {
	ReplaceTransformation t("", "x");
	REQUIRE(t.transform("abc") == "abc");
}

TEST_CASE("CompositeTransformation respects transformation order", "[transformation][composite]") {
	auto composite1 = std::make_shared<CompositeTransformation>();
	composite1->add(std::make_shared<CapitalizeTransformation>());
	composite1->add(std::make_shared<DecorateTransformation>());

	auto composite2 = std::make_shared<CompositeTransformation>();
	composite2->add(std::make_shared<DecorateTransformation>());
	composite2->add(std::make_shared<CapitalizeTransformation>());

	REQUIRE(composite1->transform("hello") == "-={ Hello }=-");
	REQUIRE(composite2->transform("hello") == "-={ hello }=-");
}


TEST_CASE("CompositeTransformation with no steps returns input unchanged", "[transformation][composite]") {
	auto composite = std::make_shared<CompositeTransformation>();

	REQUIRE(composite->transform("hello") == "hello");
	REQUIRE(composite->transform("") == "");
}

TEST_CASE("CensorFactory implements Flyweight pattern", "[transformation][censor]") {
	SECTION("Short words share the same instance") {
		auto censor1 = CensorFactory::getCensor("bad");
		auto censor2 = CensorFactory::getCensor("bad");
		REQUIRE(censor1.get() == censor2.get());
	}

	SECTION("Long words do not share instances") {
		auto censor1 = CensorFactory::getCensor("verylongword");
		auto censor2 = CensorFactory::getCensor("verylongword");
		REQUIRE(censor1.get() != censor2.get());
	}
}
