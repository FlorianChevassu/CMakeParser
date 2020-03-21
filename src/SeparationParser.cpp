#include "SeparationParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::Separation>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::Separation;

    auto tmp = Parser<ElementType::Space>{}.Parse(r);
    if (tmp)
    {
      result.children.push_back(*tmp);
      result.range = Range{ r.begin, tmp->range.end };
      return result;
    }
    tmp = Parser<ElementType::LineEnding>{}.Parse(r);
    if (tmp)
    {
      result.children.push_back(*tmp);
      result.range = Range{ r.begin, tmp->range.end };
      return result;
    }

    Error err;
    err.message = "A separation is either a space or a line ending.";
    err.context = r.begin;
    return tl::make_unexpected(err);
  }
}
