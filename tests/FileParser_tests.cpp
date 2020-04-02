#include "FileParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("FileParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::File> parser;

  SECTION("Parse")
  {
    std::string_view script;
    SECTION("Empty file")
    {
      script = ""sv;
    }

#ifndef CMAKE_PARSER_STRICT_MODE
    SECTION("Without new line at end of file")
    {
      script = "set(a b c)"sv;
    }
#endif
    
    SECTION("Command invocations")
    {
      script = "set(a b c)\n bad_name(x y z)\n"sv;
    }

    Range r{ script.begin(), script.end() };
    auto result = parser.Parse(r);
    REQUIRE(result);
    REQUIRE(result.value().range == r);
  }

  SECTION("!Parse")
  {
#ifdef CMAKE_PARSER_STRICT_MODE
    SECTION("Anything without line ending")
    {
      auto script = "set(a b c)"sv;
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
#endif
  }
}
