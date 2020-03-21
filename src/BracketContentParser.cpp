#include "BracketContentParser.hpp"

#include "BracketCloseParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  Parser<ElementType::BracketContent>::Parser(size_t i_length)
    : m_length(i_length)
  {
  }

  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::BracketContent>::Parse(Range r)
  {
    auto ClosingBracketIsValid = [len = m_length](auto it) {
      return std::all_of(it, it + len, [](Char c) { return c == '='; }) && *(it + len + 1) == ']';
    };

    Token result;
    result.type = ElementType::BracketContent;

    tl::expected<Token, Error> bracketCloseToken;
    auto firstClosingBracket = std::find_if(r.begin, r.end, [](Char c) { return c == ']'; });
    do
    {
      if (firstClosingBracket == r.end)
      {
        Error err;
        err.message = "No matching bracket close.";
        err.context = r;
        return tl::make_unexpected(err);
      }
      bracketCloseToken = Parser<ElementType::BracketClose>{m_length}.Parse({ firstClosingBracket, r.end });
      firstClosingBracket = std::find_if(firstClosingBracket + 1, r.end, [](Char c) { return c == ']'; });
    } while (!bracketCloseToken);

    result.range = Range{ r.begin, bracketCloseToken->range.begin };
    return result;
  }
}
