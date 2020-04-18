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

    tl::expected<Token, Error> bracketArgumentChild = Parser<ElementType::BracketArgument>{}.Parse(r);
    if (bracketArgumentChild)
    {
      result.children.push_back(*bracketArgumentChild);
      result.range = Range{ r.begin, bracketArgumentChild->range.end };
      return result;
    }

    tl::expected<Token, Error> quotedArgumentChild = Parser<ElementType::QuotedArgument>{}.Parse(r);
    if (quotedArgumentChild)
    {
      result.children.push_back(*quotedArgumentChild);
      result.range = Range{ r.begin, quotedArgumentChild->range.end };
      return result;
    }

    tl::expected<Token, Error> unquotedArgumentChild = Parser<ElementType::UnquotedArgument>{}.Parse(r);
    if (unquotedArgumentChild)
    {
      result.children.push_back(*unquotedArgumentChild);
      result.range = Range{ r.begin, unquotedArgumentChild->range.end };
      return result;
    }

    Error error = Error::make().context(r).message("Could not parse argument.").children({
      Error::make().context(r).message("Could be a bracket argument but").children({ bracketArgumentChild.error() }),
      Error::make().context(r).message("Could be a quoted argument but").children({ quotedArgumentChild.error() }),
      Error::make() .context(r).message("Could be a unquoted argument but").children({ unquotedArgumentChild.error() })
     });

    return tl::make_unexpected(error);
  }
}
