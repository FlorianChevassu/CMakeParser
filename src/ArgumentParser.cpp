#include "ArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::Argument>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::Argument;

    tl::expected<Token, Error> tmp = Parser<ElementType::BracketArgument>{}.Parse(r);
    if (tmp)
    {
      result.children.push_back(*tmp);
      result.range = Range{ r.begin, tmp->range.end };
      return result;
    }
    tmp = Parser<ElementType::QuotedArgument>{}.Parse(r);
    if (tmp)
    {
      result.children.push_back(*tmp);
      result.range = Range{ r.begin, tmp->range.end };
      return result;
    }
    tmp = Parser<ElementType::UnquotedArgument>{}.Parse(r);
    if (tmp)
    {
      result.children.push_back(*tmp);
      result.range = Range{ r.begin, tmp->range.end };
      return result;
    }

    Error err;
    err.context = r.begin;
    return tl::make_unexpected(err);
  }
}
