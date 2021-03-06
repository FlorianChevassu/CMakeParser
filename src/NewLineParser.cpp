#include "NewLineParser.hpp"

#include "CommonErrors.hpp"
#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::NewLine>::Parse(Range r)
  {
    if (r.IsEmpty())
    {
      return CreateEmptyRangeError(r, R"('\n')");
    }
    else if (*r.begin != '\n')
    {
      Error err;
      err.message = R"__(Expected a '\n' character.)__";
      err.context = Range{ r.begin, r.begin + 1 };
      return tl::make_unexpected(err);
    }
    Token result;
    result.type = ElementType::NewLine;
    result.range = Range{ r.begin, r.begin + 1 };
    return result;
  }
}
