#pragma once
#include "Parser.hpp"
#include "ElementType.hpp"

namespace cmake::language
{
  template <>
  class Parser<ElementType::Arguments>
  {
  public:
    tl::expected<Token, Error> Parse(Range r);
  };
}