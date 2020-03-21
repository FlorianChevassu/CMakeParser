#include "UnquotedElementParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::UnquotedElement>::Parse(Range r)
  {
    auto IsInvalidCharacter = [](Char c) {
      return c == ' ' ||
        c == '(' ||
        c == ')' ||
        c == '#' ||
        c == '\"' ||
        c == '\\';
    };

    if (r.IsEmpty())
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::UnquotedElement;

    auto tmp = Parser<ElementType::EscapeSequence>{}.Parse(r);
    if (tmp)
    {
      result.children.push_back(*tmp);
      result.range = tmp->range;
      return result;
    }

    if (IsInvalidCharacter(*r.begin))
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    result.range = Range{ r.begin, r.begin + 1 };
    return result;
  }
}
