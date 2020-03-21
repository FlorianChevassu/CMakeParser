#include "SeparatedArgumentsParser.hpp"

#include "Error.hpp"
#include "Range.hpp"
#include "Token.hpp"

namespace cmake::language
{
  //-----------------------------------------------------------------------------
  tl::expected<Token, Error> Parser<ElementType::SeparatedArguments>::Parse(Range r)
  {
    auto firstCondition = [&]() -> tl::expected<Token, Error> {
      auto tmp = Parser<ElementType::Separation>{}.Parse(r);
      if (!tmp)
      {
        Error err;
        err.message = "There must be a separation between arguments";
        err.context = r.begin;
        return tl::make_unexpected(err);
      }

      Token result;
      result.type = ElementType::SeparatedArguments;

      tl::expected<Token, Error> lastSeparation;
      do
      {
        result.children.push_back(*tmp);
        lastSeparation = tmp;
        tmp = Parser<ElementType::Separation>{}.Parse(Range{ tmp->range.end, r.end });
      } while (tmp);

      auto argument = Parser<ElementType::Argument>{}.Parse(Range{ lastSeparation->range.end, r.end });

      if (argument)
      {
        result.children.push_back(*argument);
        result.range = Range{ r.begin, argument->range.end };
      }
      else
      {
        result.range = Range{ r.begin, lastSeparation->range.end };
      }

      return result;
    }();

    if (firstCondition)
    {
      return firstCondition;
    }

    auto secondCondition = [&]() -> tl::expected<Token, Error> {
      Token result;
      result.type = ElementType::SeparatedArguments;

      tl::expected<Token, Error> tmp = Parser<ElementType::Separation>{}.Parse(r);
      tl::expected<Token, Error> lastSeparation = tmp;
      while (tmp)
      {
        result.children.push_back(*tmp);
        lastSeparation = tmp;
        tmp = Parser<ElementType::Separation>{}.Parse(Range{ tmp->range.end, r.end });
      };

      auto currentRange = lastSeparation ? lastSeparation->range : Range{ r.begin, r.begin };

      if (currentRange.end == r.end || *currentRange.end != '(')
      {
        Error err;
        err.message = "Separated arguments must start with a \'(\'";
        err.context = currentRange.end;
        return tl::make_unexpected(err);
      }

      auto arguments = Parser<ElementType::Arguments>{}.Parse(Range{ currentRange.end + 1, r.end });

      if (!arguments)
      {
        return arguments;
      }
      result.children.push_back(*arguments);

      if (arguments->range.end >= r.end || *arguments->range.end != ')')
      {
        Error err;
        err.message = "Separated arguments must end with a \')\'";
        err.context = arguments->range.end;
        return tl::make_unexpected(err);
      }
      result.range = Range{ r.begin, arguments->range.end + 1 };
      return result;
    }();

    if (secondCondition)
    {
      return secondCondition;
    }

    Error err;
    err.message = "Failed to parse separated arguments.";
    err.context = r.begin;
    {
      Error firstMessage;
      firstMessage.message = "Might be:";
      firstMessage.context = r.begin;
      firstMessage.children = firstCondition.error().children;
      err.children.push_back(firstMessage);
    }

    {
      Error secondMessage;
      secondMessage.message = "Or:";
      secondMessage.context = r.begin;
      secondMessage.children = secondCondition.error().children;
      err.children.push_back(secondMessage);
    }
    return tl::make_unexpected(err);
  }
}
