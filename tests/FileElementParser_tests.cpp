#include "FileElementParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("FileElementParser", "[Parser]")
{
  using namespace cmake::language;
  Parser<ElementType::FileElement> parser;

  SECTION("Parse")
  {
    std::string script;
    SECTION("Command invocation without end line comment")
    {
      script = "set(a b c)\n";
    }

    SECTION("Command invocation with end line comment")
    {
      script = "set(a b c)# comment\n";
    }

#ifndef CMAKE_PARSER_STRICT_MODE
    SECTION("Command invocation with end line comment separated by space")
    {
      script = "set(a b c) # comment\n";
    }
#endif

    SECTION("Bracket comment")
    {
      script = "#[[ line 1 \n line 2 ]]\n";
    }

    SECTION("Multiple bracket comments")
    {
      script = "#[[ line 1 \n line 2 ]]   #[[ line 4 \n line 5 ]]  \n";
    }

    SECTION("Empty line")
    {
      script = "\n";
    }

    SECTION("Only spaces")
    {
      script = "   \n";
    }
    SECTION("Only one comment")
    {
      script = "# comment \n";
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
      std::string script = "set(a b c)";
      Range r{ script.begin(), script.end() };
      auto result = parser.Parse(r);
      REQUIRE(!result);
    }
#endif
  }
}
