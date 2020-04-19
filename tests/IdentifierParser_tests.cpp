#include "IdentifierParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("IdentifierParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::Identifier> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      auto script = "Upper_and_Lower_with_1_number"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Start with a number")
    {
      auto script = "0_bad"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Start with some spaces")
    {
      auto script = "\nbad"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Use special characters")
    {
      auto script = "dollar_$_is_not_valid"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 7 });
    }
  }
}
