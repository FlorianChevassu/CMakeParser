#include "SeparatedArgumentsParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("SeparatedArgumentsParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::SeparatedArguments> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = " a";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With parentheses")
    {
      std::string script = "(a b c)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With multiple parentheses")
    {
      std::string script = "((a b c))";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With inner parentheses")
    {
      std::string script = "(a (b) c)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("With missing parentheses")
    {
      std::string script = "(a b c";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
