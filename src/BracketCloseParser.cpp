#include "BracketCloseParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <algorithm>

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  Parser<ElementType::BracketClose>::Parser(size_t i_length)
    : m_length(i_length)
  {
  }

  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::BracketClose>::Parse(Range r)
  {
    if (*r.begin != ']')
    {
      Error err;
      err.message = fmt::format("Expected \']\', got \'{}\'", *r.begin);
      err.context = r;
      return tl::make_unexpected(err);
    }

    // Make sure we have enough characters
    auto dist = std::distance(r.begin, r.end);
    if (dist < std::ptrdiff_t(m_length + 1))
    {
      Error err;
      err.message = fmt::format("Expected {} \'=\' characters, got only {}", m_length, dist);
      err.context = r;
      return tl::make_unexpected(err);
    }

    if (r.begin + 1 >= r.end)
    {
      Error err;
      err.message = "No matching closing bracket";
      err.context = r;
      return tl::make_unexpected(err);
    }

    if (!std::all_of(r.begin + 1, r.begin + 1 + m_length, [](char c) { return c == '='; }) ||
      *(r.begin + m_length + 1) != ']')
    {
      Error err;
      err.message = fmt::format("Expected {} \'=\' characters, and a \']\', but got \"{}\"", m_length, std::string_view(&*(r.begin + 1), m_length + 1));
      err.context = r;
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::BracketClose;
    result.range = Range{ r.begin, r.begin + m_length + 2 };
    return result;
  }
}
