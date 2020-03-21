#include "NewLineParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("NewLineParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::NewLine> parser;

  SECTION("Parse")
  {
    SECTION("New line")
    {
      std::string script = "\n";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Empty range")
    {
      std::string script = "";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Multiple new lines")
    {
      std::string script = "\n\n";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 1 });
    }
  }
}
