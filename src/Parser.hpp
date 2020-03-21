#pragma once

#include "expected.hpp"

namespace cmake::language
{
  struct Error;
  struct Range;
  struct Token;
  enum class ElementType;

  template <ElementType ET>
  class Parser
  {
  public:
    tl::expected<Token, Error> Parse(Range r);
  };
}
