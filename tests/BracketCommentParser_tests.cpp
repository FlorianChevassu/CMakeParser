#include "BracketCommentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("BracketCommentParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::BracketComment> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "#[[ comment \n comment]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
      // Bracket open, content and close.
      REQUIRE(result.value().children.size() == 3);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Without \'#\'")
    {
      std::string script = "[[ test ]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
    SECTION("With space between \'#\' and bracket open")
    {
      std::string script = "# [[ test ]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
