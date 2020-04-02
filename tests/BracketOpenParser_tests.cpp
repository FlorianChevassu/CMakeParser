#include "BracketOpenParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("BracketOpenParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::BracketOpen> parser;

  SECTION("Parse")
  {
    SECTION("Without \'=\'")
    {
      auto script = "[["sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With \'=\'")
    {
      auto script = "[===["sv;
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
      auto script = " [["sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With only one bracket")
    {
      auto script = "["sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With something else than \'=\'")
    {
      auto script = "[=a=["sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
