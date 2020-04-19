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

    //-----------------------------------------------------------------------------
    tl::expected<Token, Error> ParseIdentifier(Range r)
    {
      auto newRange = IgnoreSpaces(r);
      return Parser<ElementType::Identifier>{}.Parse(newRange);
    }

    //-----------------------------------------------------------------------------
    tl::expected<Token, Error> ParseArguments(Range r)
    {
      auto newRange = IgnoreSpaces(r);
      if (*newRange.begin != '(')
      {
        Error err;
        err.message = "A command invocation should wrap its arguments between parenthesis.";
        err.context = newRange.begin;
        return tl::make_unexpected(err);
      }

      auto args = Parser<ElementType::Arguments>{}.Parse(Range{ newRange.begin + 1, r.end });

      auto closingParenIt = args ? args->range.end : newRange.begin + 1;
      if (closingParenIt >= r.end)
      {
        Error err;
        err.message = "Missing parenthesis at the end of the command invocation";
        err.context = closingParenIt;
        return tl::make_unexpected(err);
      }
      if (*closingParenIt != ')')
      {
        Error err;
        err.message = fmt::format("Expected \')\', got {}", *closingParenIt);
        err.context = closingParenIt;
        return tl::make_unexpected(err);
      }

      if (args)
      {
        args->range = Range{ r.begin, args->range.end + 1 };
      }
      else
      {
        args = Token{};
        args->type = ElementType::Arguments;
        args->range = Range{ r.begin, newRange.begin + 2 };
      }
      return args;
    }
  }

  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::CommandInvocation>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::CommandInvocation;

    auto identifier = ParseIdentifier(r);
    if (!identifier)
    {
      // Just forward the error
      return identifier;
    }
    result.children.push_back(*identifier);

    auto args = ParseArguments(Range{identifier->range.end, r.end});
    if (!args)
    {
      // Just forward the error
      return args;
    }
    result.children.push_back(*args);

    result.range = Range{ r.begin, args->range.end };
    return result;
  }
}
