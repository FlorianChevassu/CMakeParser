#include "EscapeSequenceParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::EscapeSequence>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::EscapeSequence;

    auto tmp = Parser<ElementType::EscapeIdentity>{}.Parse(r);
    if (tmp)
    {
      result.range = tmp->range;
      result.children.push_back(*tmp);
      return result;
    }
    tmp = Parser<ElementType::EscapeEncoded>{}.Parse(r);
    if (tmp)
    {
      result.range = tmp->range;
      result.children.push_back(*tmp);
      return result;
    }
    tmp = Parser<ElementType::EscapeSemilicon>{}.Parse(r);
    if (tmp)
    {
      result.range = tmp->range;
      result.children.push_back(*tmp);
      return result;
    }
    Error err;
    err.context = r.begin;
    return tl::make_unexpected(err);
  }
}
