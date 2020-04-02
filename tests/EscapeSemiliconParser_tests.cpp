#include "EscapeSemiliconParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeSemiliconParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::EscapeSemilicon> parser;

  SECTION("Parse")
  {
    SECTION("\\;")
    {
      auto script = "\\;"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Any other charater")
    {
      auto script = "\\a"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Without \'\\\'")
    {
      auto script = ";"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Without \';\'")
    {
      auto script = "\\"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
