#include "SpaceParser.hpp"

#include "CommonErrors.hpp"
#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::Space>::Parse(Range r)
  {
    auto IsSpace = [](Char c) { return c == '\t' || c == ' '; };
    if (r.IsEmpty())
    {
      return CreateEmptyRangeError(r, R"(' ' or '\t')");
    }
    else if (!IsSpace(*r.begin))
    {
      Error err;
      err.message = fmt::format("Expected \' \' or \'\\t\', got {}.", *r.begin);
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    Range newRange = r;
    do
    {
      ++newRange.begin;
    } while (!newRange.IsEmpty() && IsSpace(*newRange.begin));

    Token result;
    result.type = ElementType::Space;
    result.range = Range{ r.begin, newRange.begin };
    return result;
  }
}
