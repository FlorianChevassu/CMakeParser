#include "BracketOpenParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("BracketOpenParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::BracketOpen> parser;

  SECTION("Parse")
  {
    SECTION("Without \'=\'")
    {
      std::string script = "[[";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With \'=\'")
    {
      std::string script = "[===[";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
      REQUIRE(parser.GetLength() == 3);
    }
  }

  SECTION("!Parse")
  {
    SECTION("With space before")
    {
      std::string script = " [[";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With only one bracket")
    {
      std::string script = "[";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With something else than \'=\'")
    {
      std::string script = "[=a=[";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
