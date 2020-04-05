#include "CommandInvocationParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <algorithm>

namespace cmake::language
{
  namespace
  {
    //-----------------------------------------------------------------------------
    Range IgnoreSpaces(Range r)
    {
      return { std::find_if_not(r.begin, r.end, [](char c) {return std::isspace(c); }), r.end };
    }
  }

  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::CommandInvocation>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::CommandInvocation;

    auto newRange = IgnoreSpaces(r);
    auto identifier = Parser<ElementType::Identifier>{}.Parse(newRange);
    if (!identifier)
    {
      // Just forward the error
      return identifier;
    }
    result.children.push_back(*identifier);

    newRange = IgnoreSpaces(Range{ identifier->range.end, r.end });
    if (*newRange.begin != '(')
    {
      Error err;
      err.message = "A command invocation should wrap its arguments between parenthesis.";
      err.context = newRange.begin;
      return tl::make_unexpected(err);
    }

    auto args = Parser<ElementType::Arguments>{}.Parse(Range{ newRange.begin + 1, r.end });
    if (args)
    {
      result.children.push_back(*args);

      if (args->range.end >= r.end)
      {
        Error err;
        err.message = "Missing parenthesis";
        err.context = args->range.end;
        return tl::make_unexpected(err);
      }

      if (*args->range.end != ')')
      {
        Error err;
        err.message = fmt::format("Expected \')\', got {}", *args->range.end);
        err.context = args->range.end;
        return tl::make_unexpected(err);
      }
      result.range = Range{ r.begin, args->range.end + 1 };
    }
    else
    {
      if (newRange.begin + 1 == newRange.end)
      {
        Error err;
        err.message = "Missing parenthesis at the end of the command invocation";
        err.context = newRange.begin + 1;
        return tl::make_unexpected(err);
      }
      if (*(newRange.begin + 1) != ')')
      {
        Error err;
        err.message = fmt::format("Expected \')\', got {}", *(newRange.begin + 1));
        err.context = newRange.begin + 1;
        return tl::make_unexpected(err);
      }
      result.range = Range{ r.begin, newRange.begin + 2 };
    }

    return result;
  }
}
