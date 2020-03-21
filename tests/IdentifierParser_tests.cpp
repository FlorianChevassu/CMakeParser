#include "IdentifierParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("IdentifierParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::Identifier> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "Upper_and_Lower_with_1_number";
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
      std::string script = "0_bad";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Use special characters")
    {
      std::string script = "dollar_$_is_not_valid";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 7 });
    }
  }
}
