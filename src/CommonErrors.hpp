#pragma once

#include "Error.hpp"
class Range;

#include <tl/expected.hpp>

#include <string>


namespace cmake::language
{
  tl::unexpected<Error> CreateEmptyRangeError(const Range& range, const std::string& expected);
}
