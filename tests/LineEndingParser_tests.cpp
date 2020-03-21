#include "LineEndingParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("LineEndingParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::LineEnding> parser;

  SECTION("Parse")
  {
    SECTION("Comment with new line")
    {
      std::string script = "# comment \n";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
    SECTION("Only new line")
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
    SECTION("Bracket comment with new line")
    {
      std::string script = "#[[ comment ]]\n";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
