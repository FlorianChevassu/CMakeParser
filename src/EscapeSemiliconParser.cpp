#include "EscapeSemiliconParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::EscapeSemilicon>::Parse(Range r)
  {
    if (std::distance(r.begin, r.end) < 2 || *r.begin != '\\' || *(r.begin + 1) != ';')
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::EscapeSemilicon;
    result.range = Range{ r.begin, r.begin + 2 };
    return result;
  }
}
