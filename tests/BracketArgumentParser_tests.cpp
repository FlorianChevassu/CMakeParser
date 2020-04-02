#include "BracketArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("BracketArgumentParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::BracketArgument> parser;

  SECTION("Parse")
  {
    SECTION("Without \'=\'")
    {
      auto script = "[[ text ]]"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With \'=\'")
    {
      auto script = "[=[ text ]=]"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With new line")
    {
      auto script = "[=[ text \n with \n new \n lines ]=]"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("With inner bracket argument")
    {
      auto script = "[=[ [[ inner arg ]] ]=]"sv;
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
      auto script = "[=[  ]==]"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("With inner args with same numbers of \'=\'")
    {
      auto script = "[=[ [=[ ]=] ]=]"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 11 });
    }
  }
}
