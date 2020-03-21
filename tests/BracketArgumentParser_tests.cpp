#include "BracketArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("BracketArgumentParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::BracketArgument> parser;

  SECTION("Parse")
  {
    SECTION("Without \'=\'")
    {
      std::string script = "[[ text ]]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With \'=\'")
    {
      std::string script = "[=[ text ]=]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With new line")
    {
      std::string script = "[=[ text \n with \n new \n lines ]=]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With inner bracket argument")
    {
      std::string script = "[=[ [[ inner arg ]] ]=]";
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
      std::string script = "[=[  ]==]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With inner args with same numbers of \'=\'")
    {
      std::string script = "[=[ [=[ ]=] ]=]";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 11 });
    }
  }
}
