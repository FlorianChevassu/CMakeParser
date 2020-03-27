#include "FileElementParser.hpp"

#include "LineEndingParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::FileElement>::Parse(Range r)
  {
    if (r.IsEmpty())
    {
      Error err;
      err.message = "Empty range.";
      err.context = r;
      return tl::make_unexpected(std::move(err));
    }

    Token result;
    result.type = ElementType::FileElement;

    tl::expected<Token, Error> subToken = Parser<ElementType::CommandInvocation>{}.Parse(r);
    if (subToken)
    {
      result.children.push_back(*subToken);

      // This part is non standard. According to the CMake documentation,
      // spaces between a command invocation and a line ending are not allowed.
      // https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#grammar-token-file-element
#ifndef CMAKE_PARSER_STRICT_MODE
      {
        Range currentTokenRange{ subToken.value().range.end };
        tl::expected<Token, Error> lastValidCommandInvocation;
        do
        {
          lastValidCommandInvocation = subToken;
          subToken = Parser<ElementType::Space>{}.Parse(Range{ currentTokenRange.end, r.end });
          if (subToken)
          {
            currentTokenRange = subToken->range;
            result.children.push_back(*subToken);
          }
        } while (subToken);
        subToken = lastValidCommandInvocation;
      }
#endif
    }
    else
    {
      Range currentTokenRange{ r.begin, r.begin };
      tl::expected<Token, Error> lastValidCommandInvocation;
      do
      {
        lastValidCommandInvocation = subToken;
        subToken = Parser<ElementType::BracketComment>{}.Parse(Range{ currentTokenRange.end, r.end });
        if (!subToken)
        {
          subToken = Parser<ElementType::Space>{}.Parse(Range{ currentTokenRange.end, r.end });
        }
        if (subToken)
        {
          currentTokenRange = subToken->range;
          result.children.push_back(*subToken);
        }
      } while (subToken);
      subToken = lastValidCommandInvocation;
    }

    Range currentRange;
    if (result.children.empty())
    {
      currentRange = r;
    }
    else
    {
      currentRange = Range{ result.children.back().range.end, r.end };
    }

#ifdef CMAKE_PARSER_STRICT_MODE
    tl::expected<Token, Error> lineEnding = Parser<ElementType::LineEnding>{}.Parse(currentRange);
#else
    tl::expected<Token, Error> lineEnding = Parser<ElementType::LineEnding>(true).Parse(currentRange);
#endif

    if (!lineEnding)
    {
#ifdef CMAKE_PARSER_STRICT_MODE
      Error err;
      err.message = "A FileElement should end with a LineEnding.";
      err.context = Range{ currentRange.begin, currentRange.begin };
      err.children.push_back(lineEnding.error());
      return tl::make_unexpected(std::move(err));
#else
      result.range = Range{ r.begin, currentRange.begin };
#endif
    }
    else
    {
      result.children.push_back(*lineEnding);
      result.range = Range{ r.begin, lineEnding->range.end };
    }

    return result;
  }
}
