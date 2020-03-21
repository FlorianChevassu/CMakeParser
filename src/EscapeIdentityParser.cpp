#include "EscapeIdentityParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::EscapeIdentity>::Parse(Range r)
  {
    if (std::distance(r.begin, r.end) < 2 || *r.begin != '\\')
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    auto IsInvalidChar = [](Char c) {
      return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == ';';
    };

    if (IsInvalidChar(*(r.begin + 1)))
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::EscapeIdentity;
    result.range = Range{ r.begin, r.begin + 2 };
    return result;
  }
}
