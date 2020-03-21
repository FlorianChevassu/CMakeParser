#include "UnquotedElementParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("UnquotedElementParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::UnquotedElement> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "a";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("Escape sequence")
    {
      std::string script = "\\t";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Opening parenthesis")
    {
      std::string script = "(";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Closing parenthesis")
    {
      std::string script = ")";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("\'#\'")
    {
      std::string script = "#";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("\'\\\'")
    {
      std::string script = "\\";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
