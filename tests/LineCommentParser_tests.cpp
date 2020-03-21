#include "LineCommentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("LineCommentParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::LineComment> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "# comment";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Start with anything but a \'#\'")
    {
      std::string script = " # comment with space";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Start with bracket open")
    {
      std::string script = "#[[ comment";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

    SECTION("Do not match new lines")
    {
      std::string script = "# comment \n with new lines";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.begin + 10 });
    }
  }
}
