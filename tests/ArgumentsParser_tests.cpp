#include "ArgumentsParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("ArgumentsParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::Arguments> parser;

  SECTION("Parse")
  {
    SECTION("Single argument")
    {
      std::string script = "[[ text ]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("Multiple arguments")
    {
      std::string script = "arg1 arg2 \"argument 3\"";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("Arguments surrounded by parentheses")
    {
      std::string script = "(arg1 arg2) arg3 (arg4 arg5)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("Should match spaces before and after")
    {
      std::string script = " arg ";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("Should match parenthesis before and after")
    {
      std::string script = "(arg)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
  }
}
