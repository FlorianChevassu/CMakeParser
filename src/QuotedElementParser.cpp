#include "QuotedElementParser.hpp"

#include "CommonErrors.hpp"
#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::QuotedElement>::Parse(Range r)
  {
    auto IsValidCharacter = [](char c) { return c != '\\' && c != '"'; };

    if (r.IsEmpty())
    {
      return CreateEmptyRangeError(r, "quoted element");
    }

    Token result;
    result.type = ElementType::QuotedElement;

    if (IsValidCharacter(*r.begin))
    {
      result.range = Range{ r.begin, r.begin + 1 };
      return result;
    }
    else
    {
      auto tmp = Parser<ElementType::EscapeSequence>{}.Parse(r);
      if (!tmp)
      {
        tmp = Parser<ElementType::QuotedContinuation>{}.Parse(r);
      }

      if (tmp)
      {
        result.range = Range{ r.begin, tmp->range.end };
        result.children.push_back(*tmp);
        return result;
      }
    }

    Error err;
    err.context = r.begin;
    return tl::make_unexpected(err);
  }
}
