#include "BracketOpenParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::BracketOpen>::Parse(Range r)
  {
    if (r.IsEmpty())
    {
      Error err;
      err.message = "Expected \'[\', got an empty range.";
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    if (*r.begin != '[')
    {
      Error err;
      err.message = fmt::format("Expected \'[\', got \'{}\'", *r.begin);
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    if (r.begin + 1 == r.end)
    {
      Error err;
      err.message = "The opening bracket contains only one \'[\'";
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    auto firstNonEqual = std::find_if(r.begin + 1, r.end, [](Char c) { return c != '='; });
    this->m_length = firstNonEqual - r.begin - 1;
    if (*firstNonEqual != '[')
    {
      Error err;
      err.message = fmt::format("Expected \'[\', got \'{}\'", *r.begin);
      err.context = r.begin;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::BracketOpen;
    result.range = Range{ r.begin, firstNonEqual + 1 };
    return result;
  }
}
