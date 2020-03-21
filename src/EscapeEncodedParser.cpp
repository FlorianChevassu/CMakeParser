#include "EscapeEncodedParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::EscapeEncoded>::Parse(Range r)
  {
    if (std::distance(r.begin, r.end) < 2 || *r.begin != '\\')
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }
    Char c = *(r.begin + 1);
    if (c != 't' && c != 'r' && c != 'n')
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::EscapeEncoded;
    result.range = Range{ r.begin, r.begin + 2 };
    return result;
  }
}
