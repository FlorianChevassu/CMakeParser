#pragma once
#include "Parser.hpp"
#include "ElementType.hpp"

namespace cmake::language
{
  template <>
  class Parser<ElementType::BracketClose>
  {
  public:
    Parser(size_t i_length);
    tl::expected<Token, Error> Parse(Range r);

  private:
    size_t m_length;
  };
}