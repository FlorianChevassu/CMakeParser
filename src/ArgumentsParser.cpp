#include "ArgumentsParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::Arguments>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::Arguments;

    tl::expected<Token, Error> argument = Parser<ElementType::Argument>{}.Parse(r);
    if (argument)
    {
      result.children.push_back(*argument);
    }

    Range nextRange = argument ? Range{ argument->range.end, r.end } : r;
    tl::expected<Token, Error> separatedArgs = Parser<ElementType::SeparatedArguments>{}.Parse(nextRange);
    tl::expected<Token, Error> lastSeparatedArgs = separatedArgs;
    while (separatedArgs)
    {
      result.children.push_back(*separatedArgs);
      lastSeparatedArgs = separatedArgs;
      separatedArgs = Parser<ElementType::SeparatedArguments>{}.Parse(Range{ separatedArgs->range.end, r.end });
    }

    if (!lastSeparatedArgs)
    {
      if (!argument)
      {
        Error err;
        err.message = "No argument available.";
        err.context = r.begin;
        return tl::make_unexpected(err);
      }
      result.range = Range{ r.begin, argument->range.end };
    }
    else
    {
      result.range = Range{ r.begin, lastSeparatedArgs->range.end };
    }

    return result;
  }
}
