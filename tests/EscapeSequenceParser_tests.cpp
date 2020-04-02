#include "EscapeSequenceParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeSequenceParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::EscapeSequence> parser;

  SECTION("Parse")
  {
    SECTION("Anything after \'\\\'")
    {
      std::string_view script;
      SECTION("Escape identity")
      {
        script = "\\$"sv;
      }
      SECTION("Escape semilicon")
      {
        script = "\\;"sv;
      }
      SECTION("Escape encoded")
      {
        script = "\\t"sv;
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
      auto script = "$"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
