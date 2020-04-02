#include "EscapeIdentityParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("EscapeIdentityParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::EscapeIdentity> parser;

  SECTION("Parse")
  {
    SECTION("\\$")
    {
      auto script = "\\$"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("\\&")
    {
      auto script = "\\&"sv;
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
        auto script = "\\a"sv;
        Range r{ script.begin(), script.end() };
        auto result = parser.Parse(r);
        REQUIRE(!result);
      }
      SECTION("\\1")
      {
        auto script = "\\1"sv;
        Range r{ script.begin(), script.end() };
        auto result = parser.Parse(r);
        REQUIRE(!result);
      }
      SECTION("\\;")
      {
        auto script = "\\;"sv;
        Range r{ script.begin(), script.end() };
        auto result = parser.Parse(r);
        REQUIRE(!result);
      }
    }
  }
}
