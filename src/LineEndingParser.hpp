#pragma once
#include "Parser.hpp"
#include "ElementType.hpp"

namespace cmake::language
{
  template <>
  class Parser<ElementType::LineEnding>
  {
#ifndef CMAKE_PARSER_STRICT_MODE
  public:
    Parser(bool i_acceptNoNewLine = false) : m_acceptNoNewLine(i_acceptNoNewLine) {}
  private:
    bool m_acceptNoNewLine = false;
#endif
  public:
    tl::expected<Token, Error> Parse(Range r);
  };
}