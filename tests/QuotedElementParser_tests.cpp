#include "QuotedElementParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("QuotedElementParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::QuotedElement> parser;

  SECTION("Parse")
  {
    SECTION("Simple character")
    {
      auto script = "t"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
    SECTION("Escaped character")
    {
      auto script = "\\\""sv;
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
      auto script = "\""sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
