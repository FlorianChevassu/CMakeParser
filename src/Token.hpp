#pragma once
#include "ElementType.hpp"
#include "Range.hpp"

#include <vector>

namespace cmake::language
{
  struct Token
  {
    ElementType type;
    Range range;
    std::vector<Token> children;
  };
}
