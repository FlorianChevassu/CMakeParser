#include "QuotedArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("QuotedArgumentParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::QuotedArgument> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "\"quoted arg with spaces and;semicolons\"";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Without quotes")
    {
      std::string script = "arg without quotes";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Without closing quote")
    {
      std::string script = "\"arg without closing quote";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Empty range")
    {
      std::string script = "";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
  }
}
