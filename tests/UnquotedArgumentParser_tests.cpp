#include "UnquotedArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("UnquotedArgumentParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::UnquotedArgument> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      std::string script = "a_valid_text";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

    SECTION("Escape sequence")
    {
      std::string script = "a_text_with_\\t";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
  }

  SECTION("!Parse")
  {
    SECTION("Opening parenthesis")
    {
      std::string script = "text_with_(";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.end - 1 });
    }

    SECTION("Closing parenthesis")
    {
      std::string script = "text_with_)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.end - 1 });
    }

    SECTION("\'#\'")
    {
      std::string script = "text_with_#";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.end - 1 });
    }

    SECTION("\'\\\'")
    {
      std::string script = "text_with_\\";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == Range{ r.begin, r.end - 1 });
    }
  }
}
