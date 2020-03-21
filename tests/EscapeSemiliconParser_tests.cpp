#include "EscapeSemiliconParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeSemiliconParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::EscapeSemilicon> parser;

  SECTION("Parse")
  {
    SECTION("\\;")
    {
      std::string script = "\\;";
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
      std::string script = "\\a";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Without \'\\\'")
    {
      std::string script = ";";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Without \';\'")
    {
      std::string script = "\\";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
