#include "QuotedContinuationParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("QuotedContinuationParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::QuotedContinuation> parser;

  SECTION("Parse")
  {
    SECTION("Classic case")
    {
      auto script = "\\\n"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }

#ifndef CMAKE_PARSER_STRICT_MODE
    SECTION("With space before new line")
    {
      auto script = "\\ \n"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(result);
      REQUIRE(result.value().range == r);
    }
#endif
  }

  SECTION("!Parse")
  {
    SECTION("Without new line")
    {
      auto script = "\\"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }

#ifdef CMAKE_PARSER_STRICT_MODE
    SECTION("With space before new line")
    {
      auto script = "\\ \n"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
#endif
  }
}
