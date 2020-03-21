#pragma once
#include "Parser.hpp"
#include "ElementType.hpp"

namespace cmake::language
{
  template <>
  class Parser<ElementType::BracketOpen>
  {
  public:
    tl::expected<Token, Error> Parse(Range r);

    size_t GetLength() { return m_length; }

  private:
    size_t m_length;
  };
}