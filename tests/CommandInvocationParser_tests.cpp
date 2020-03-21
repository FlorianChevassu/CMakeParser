#include "CommandInvocationParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("CommandInvocationParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::CommandInvocation> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "set(a b \"c\")";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With space before parenthesis")
    {
      std::string script = "set  (a b \"c\")";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With new line in args")
    {
      std::string script = "set  (a b \n \"c\")";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With space before")
    {
      std::string script = " set(a b c)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With new line before parenthesis")
    {
      std::string script = "set \n (a b c)";
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
      std::string script = "set(a";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
