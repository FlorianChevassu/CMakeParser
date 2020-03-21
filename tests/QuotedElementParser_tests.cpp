#include "QuotedElementParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("QuotedElementParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::QuotedElement> parser;

  SECTION("Parse")
  {
    SECTION("Simple character")
    {
      std::string script = "t";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
    SECTION("Escaped character")
    {
      std::string script = "\\\"";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Quote")
    {
      std::string script = "\"";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
