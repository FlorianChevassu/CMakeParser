#include "BracketCloseParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("BracketCloseParser", "[Parser]")
{
  using namespace cmake::language;

  SECTION("Parse")
  {
    SECTION("Without \'=\'")
    {
      Parser<ElementType::BracketClose> parser(0);
      std::string script = "]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With \'=\'")
    {
      Parser<ElementType::BracketClose> parser(1);
      std::string script = "]=]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("With different numbers of \'=\'")
    {
      Parser<ElementType::BracketClose> parser(1);
      std::string script = "]==]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With something else than \'=\'")
    {
      Parser<ElementType::BracketClose> parser(1);
      std::string script = "]a]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }

}
