#include "ArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"
TEST_CASE("ArgumentParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::Argument> parser;

  SECTION("Parse")
  {
    SECTION("BracketArgument")
    {
      auto script = "[[ text ]]"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().type == ElementType::Argument);
      REQUIRE(result.value().range == r);
    }

    SECTION("QuotedArgument")
    {
      auto script = "\"This is an argument !\""sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().type == ElementType::Argument);
      REQUIRE(result.value().range == r);
    }

    SECTION("UnquotedArgument")
    {
      auto script = "This_is_an_argument"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().type == ElementType::Argument);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Should match only the first argument")
    {
      auto script = "arg1 \"arg2\" arg3"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 4 });
    }

    SECTION("Should not match with spaces before")
    {
      auto script = "  arg"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Should not match with parentheses")
    {
      auto script = "(arg)"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
