#include "FileElementParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "catch.hpp"

TEST_CASE("FileElementParser", "[Parser]")
{
  using namespace std::literals;
  using namespace cmake::language;
  Parser<ElementType::FileElement> parser;

  SECTION("Parse")
  {
    std::string_view script;
    SECTION("Command invocation without end line comment")
    {
      script = "set(a b c)\n"sv;
    }

    SECTION("Command invocation with end line comment")
    {
      script = "set(a b c)# comment\n"sv;
    }

#ifndef CMAKE_PARSER_STRICT_MODE
    SECTION("Command invocation without end line comment separated by space")
    {
      script = "set(a b c) # comment\n"sv;
    }

    SECTION("Command invocation without end line")
    {
      script = "set(a b c) # comment "sv;
    }
#endif

    SECTION("Bracket comment")
    {
      script = "#[[ line 1 \n line 2 ]]\n"sv;
    }

    SECTION("Multiple bracket comments")
    {
      script = "#[[ line 1 \n line 2 ]]   #[[ line 4 \n line 5 ]]  \n"sv;
    }

    SECTION("Empty line")
    {
      script = "\n"sv;
    }

    SECTION("Only spaces")
    {
      script = "   \n"sv;
    }
    SECTION("Only one comment")
    {
      script = "# comment \n"sv;
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
