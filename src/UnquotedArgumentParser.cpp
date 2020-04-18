#include "UnquotedArgumentParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::UnquotedArgument>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::UnquotedArgument;

    auto tmp = Parser<ElementType::UnquotedElement>{}.Parse(r);
    if (!tmp)
    {
      Error err = Error::make()
        .context(r)
        .message("Could not parse unquoted argument.")
        .children({ tmp.error() });
      return tl::make_unexpected(err);
    }

    auto lastValidRange = tmp->range;
    while (tmp)
    {
      result.children.push_back(*tmp);
      lastValidRange = tmp->range;
      tmp = Parser<ElementType::UnquotedElement>{}.Parse(Range{ tmp->range.end, r.end });
    }
    result.range = Range{ r.begin, lastValidRange.end };
    return result;
  }
}
