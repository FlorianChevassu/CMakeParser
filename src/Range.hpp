#pragma once
#include <string>
#include <iostream>

namespace cmake::language
{

  using It = std::string::const_iterator;
  using Char = char;

  struct Context
  {
    size_t line;
    size_t column;
  };

  struct Range
  {
    Range() = default;
    Range(It b);
    Range(It b, It e);
    It begin;
    It end;

    bool IsEmpty() const;

    bool operator==(const Range& i_other) const;
    bool operator!=(const Range& i_other) const;

    Context GetContext(It i_position) const;
    friend std::ostream& operator<<(std::ostream& i_os, const Range& i_range);
  };

  std::ostream& operator<<(std::ostream& i_os, const Range& i_range);

}
