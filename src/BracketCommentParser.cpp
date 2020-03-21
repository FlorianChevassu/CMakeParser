#include "BracketCommentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::BracketComment>::Parse(Range r)
  {
    if (r.IsEmpty() || *r.begin != '#')
    {
      Error err;
      err.message = "A bracket comment should start with a`\'#\'";
      err.context = r;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::BracketComment;

    auto tmp = Parser<ElementType::BracketArgument>{}.Parse(Range{ r.begin + 1, r.end });
    if (!tmp)
    {
      return tmp;
    }
    result.range = Range{ r.begin, tmp->range.end };
    return result;
  }
}
