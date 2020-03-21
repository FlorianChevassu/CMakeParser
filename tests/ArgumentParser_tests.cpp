#include "ArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("ArgumentParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::Argument> parser;

  SECTION("Parse")
  {
    SECTION("BracketArgument")
    {
      std::string script = "[[ text ]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("QuotedArgument")
    {
      std::string script = "\"This is an argument !\"";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("UnquotedArgument")
    {
      std::string script = "This_is_an_argument";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Should match only the first argument")
    {
      std::string script = "arg1 \"arg2\" arg3";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 4 });
    }

    SECTION("Should not match with spaces before")
    {
      std::string script = "  arg";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Should not match with parentheses")
    {
      std::string script = "(arg)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
