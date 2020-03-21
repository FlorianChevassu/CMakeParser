#include "IdentifierParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::Identifier>::Parse(Range r)
  {
    auto IsValidFirstChar = [](Char c) {
      return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
    };

    if (r.IsEmpty() || !IsValidFirstChar(*r.begin))
    {
      Error err;
      err.message = "An identifier can only contain alphanumerics or underscores.";
      err.context = Range{ r.begin };
      return tl::make_unexpected(err);
    }

    auto IsValidChar = [=](Char c) {
      return IsValidFirstChar(c) ||
        (c >= '0' && c <= '9');
    };

    Token result;
    result.type = ElementType::Identifier;

    auto firstBadChar = std::find_if(r.begin, r.end, [=](Char c) { return !IsValidChar(c); });

    result.range = Range{ r.begin, firstBadChar };
    return result;
  }
}
