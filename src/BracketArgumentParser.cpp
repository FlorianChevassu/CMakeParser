#include "BracketArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

#include "BracketOpenParser.hpp"
#include "BracketContentParser.hpp"
#include "BracketCloseParser.hpp"


#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::BracketArgument>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::BracketArgument;

    Parser<ElementType::BracketOpen> bop;
    auto tmp = bop.Parse(r);
    if (!tmp.has_value())
    {
      return tmp;
    }
    result.children.push_back(*tmp);

    tmp = Parser<ElementType::BracketContent>{ bop.GetLength() }.Parse(Range{ tmp->range.end, r.end });
    if (!tmp)
    {
      return tmp;
    }
    result.children.push_back(*tmp);

    tmp = Parser<ElementType::BracketClose>{ bop.GetLength() }.Parse(Range{ tmp->range.end, r.end });
    if (!tmp)
    {
      return tmp;
    }
    result.children.push_back(*tmp);

    result.range = Range{ r.begin, tmp->range.end };
    return result;
  }
}
