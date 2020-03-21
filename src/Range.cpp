#include "Range.hpp"

#include <algorithm>
#include <iostream>

namespace cmake::language
{
  Range::Range(It b, It e)
    : begin(b), end(e)
  {
  }

  Range::Range(It b)
    : Range(b, b)
  {
  }

  bool Range::IsEmpty() const
  {
    return this->begin == this->end;
  }

  bool Range::operator==(const Range& i_other) const
  {
    return this->begin == i_other.begin && this->end == i_other.end;
  }

  bool Range::operator!=(const Range& i_other) const
  {
    return !(*this == i_other);
  }

  Context Range::GetContext(It i_position) const
  {
    Context result;

    // Get line number
    result.line = std::count(this->begin, this->end, '\n') + 1;

    auto begin = std::make_reverse_iterator(this->end);
    auto end = std::make_reverse_iterator(this->begin);
    auto lastLineIt = std::find(begin, end, '\n');
    if (lastLineIt != end)
    {
      result.column = std::distance(lastLineIt.base(), this->end);
    }
    else
    {
      result.column = std::distance(this->begin, this->end);
    }

    return result;
  }

  std::ostream& operator<<(std::ostream& i_os, const Range& i_range)
  {
    i_os << '\"' << std::string_view(&*i_range.begin, std::distance(i_range.begin, i_range.end)) << '\"';
    return i_os;
  }

}