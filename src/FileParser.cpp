#include "FileParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::File>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::File;

    tl::expected<Token, Error> fileElement = Parser<ElementType::FileElement>{}.Parse(r);
    tl::expected<Token, Error> lastValidFileElement = fileElement;
    while (fileElement)
    {
      result.children.push_back(*fileElement);
      lastValidFileElement = fileElement;
      fileElement = Parser<ElementType::FileElement>{}.Parse(Range{ fileElement->range.end, r.end });
    }
    if (lastValidFileElement)
    {
      result.range = Range{ r.begin, lastValidFileElement->range.end };
    }
    else
    {
      result.range = Range{ r.begin, r.begin };
    }

    return result;
  }
}
