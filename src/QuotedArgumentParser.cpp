#include "QuotedArgumentParser.hpp"

#include "CommonErrors.hpp"
#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  tl::unexpected<Error> CreateMissingEndingQuoteError(const Range& range)
  {
    Error error = Error::make()
      .context(range)
      .message("Could not parse quoted argument. Missing ending quotes.");
    return tl::make_unexpected(error);
  }

  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::QuotedArgument>::Parse(Range r)
  {
    if (r.IsEmpty())
    {
      return CreateEmptyRangeError(r, "quoted argument");
    }

    if (*r.begin != '\"')
    {
      Error err;
      err.context = r.begin;
      err.message = "Could not parse quoted argument. Missing starting quotes.";
      return tl::make_unexpected(err);
    }

    Token result;
    result.type = ElementType::QuotedArgument;

    Range currentRange = { r.begin + 1, r.end };
    tl::expected<Token, Error> quotedElement;
    do
    {
      quotedElement = Parser<ElementType::QuotedElement>{}.Parse(currentRange);
      if (quotedElement)
      {
        result.children.push_back(*quotedElement);
        currentRange = Range{ quotedElement->range.end, r.end };
      }
    } while (quotedElement);

    if (!result.children.empty())
    {
      if (currentRange.begin == r.end || *currentRange.begin != '\"')
      {
        return CreateMissingEndingQuoteError(r);
      }

      result.range = Range{ r.begin, currentRange.begin + 1 };
    }
    else
    {
      if (std::distance(r.begin, r.end) < 2)
      {
        return CreateMissingEndingQuoteError(r);
      }

      result.range = Range{ r.begin, r.begin + 2 };
    }
    return result;
  }
}
