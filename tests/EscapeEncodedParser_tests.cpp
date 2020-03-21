#include "EscapeEncodedParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeEncodedParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::EscapeEncoded> parser;

  SECTION("Parse")
  {
    SECTION("Tab")
    {
      std::string script = "\\t";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
    SECTION("Return")
    {
      std::string script = "\\r";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
    SECTION("New line")
    {
      std::string script = "\\n";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Any other character")
    {
      std::string script = "\\a";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("No character")
    {
      std::string script = "\\";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("No \'\\\'")
    {
      std::string script = "a";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
