#include "EscapeSequenceParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeSequenceParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::EscapeSequence> parser;

  SECTION("Parse")
  {
    SECTION("Anything after \'\\\'")
    {
      std::string script;
      SECTION("Escape identity")
      {
        script = "\\$";
      }
      SECTION("Escape semilicon")
      {
        script = "\\;";
      }
      SECTION("Escape encoded")
      {
        script = "\\t";
      }
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Without \'\\\'")
    {
      std::string script = "$";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
