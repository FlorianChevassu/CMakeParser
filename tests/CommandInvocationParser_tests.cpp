#include "CommandInvocationParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("CommandInvocationParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::CommandInvocation> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      auto script = "set(a b \"c\")"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With space before parenthesis")
    {
      auto script = "set  (a b \"c\")"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With new line in args")
    {
      auto script = "set  (a b \n \"c\")"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With space before")
    {
      auto script = " set(a b c)"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With new line before parenthesis")
    {
      auto script = "set \n (a b c)"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("With missing parenthesis")
    {
      auto script = "set(a"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
