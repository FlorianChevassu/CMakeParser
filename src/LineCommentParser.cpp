#include "LineCommentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::LineComment>::Parse(Range r)
  {
    if (r.IsEmpty() || *r.begin != '#')
    {
      Error err;
      err.message = "A line comment should start with a \'#\' character.";
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    // Make sure the comment does not start with a BracketOpen.
    auto tmp = Parser<ElementType::BracketOpen>{}.Parse(Range{ r.begin + 1, r.end });
    if (tmp)
    {
      Error err;
      err.message = "A line comment should not start with a bracket open.";
      err.context = r.begin + 1;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::LineComment;

    // Match everything until a new line.
    auto it = std::find_if(r.begin, r.end, [](char c) { return c == '\n'; });
    result.range = Range{ r.begin, it };
    return result;
  }
}
