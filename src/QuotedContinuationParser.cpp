#include "QuotedContinuationParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include <algorithm>

namespace cmake::language
{
  namespace
  {
    //-----------------------------------------------------------------------------
    Range IgnoreSpaces(Range r)
    {
      return { std::find_if_not(r.begin, r.end, [](char c) {return std::isspace(c) && c != '\n'; }), r.end };
    }
  }

  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::QuotedContinuation>::Parse(Range r)
  {
    if (std::distance(r.begin, r.end) < 2 || *r.begin != '\\')
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }
    Range tmp = r;
    tmp.begin += 1;
#ifndef CMAKE_PARSER_STRICT_MODE
    // Non standard CMake: ignore spaces after the quoted continuation character.
    tmp = IgnoreSpaces(tmp);
#endif
    auto res = Parser<ElementType::NewLine>{}.Parse(tmp);
    if (!res)
    {
      Error err;
      err.context = r.begin;
      return tl::make_unexpected(err);
    }
    Token result;
    result.type = ElementType::QuotedContinuation;
    result.children.push_back(*res);
    result.range = Range{ r.begin, res->range.end };
    return result;
  }
}
