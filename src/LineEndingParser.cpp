#include "LineEndingParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::LineEnding>::Parse(Range r)
  {
    Token result;
    result.type = ElementType::LineEnding;
    auto lineComment = Parser<ElementType::LineComment>{}.Parse(r);
    Range newRange = r;
    if (lineComment)
    {
      result.children.push_back(*lineComment);
      newRange.begin = lineComment->range.end;
    }
    auto newLine = Parser<ElementType::NewLine>{}.Parse(newRange);
    if (!newLine)
    {
#ifndef CMAKE_PARSER_STRICT_MODE
      if (!m_acceptNoNewLine)
      {
        Error err;
        err.message = "A LineEnding should end with a NewLine.";
        err.context = Range{ newRange.begin, newRange.begin };
        return tl::make_unexpected(err);
      }
      else
      {
        result.range = Range{ r.begin, newRange.end };
      }
#endif
    }
    else
    {
      result.children.push_back(*newLine);
      result.range = Range{ r.begin, newLine->range.end };
    }
    return result;
  }
}
