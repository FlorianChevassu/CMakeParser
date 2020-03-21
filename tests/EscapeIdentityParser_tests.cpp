#include "EscapeIdentityParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeIdentityParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::EscapeIdentity> parser;

  SECTION("Parse")
  {
    SECTION("\\$")
    {
      std::string script = "\\$";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("\\&")
    {
      std::string script = "\\&";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Any alphanumerci charater")
    {
      SECTION("\\a")
      {
        std::string script = "\\a";
        Range r{ script.begin(), script.end() };
        auto result = parser.Parse(r);
        REQUIRE(!result);
      }
      SECTION("\\1")
      {
        std::string script = "\\1";
        Range r{ script.begin(), script.end() };
        auto result = parser.Parse(r);
        REQUIRE(!result);
      }
      SECTION("\\;")
      {
        std::string script = "\\;";
        Range r{ script.begin(), script.end() };
        auto result = parser.Parse(r);
        REQUIRE(!result);
      }
    }
  }
}
