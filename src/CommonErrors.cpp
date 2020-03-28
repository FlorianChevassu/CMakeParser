#include "CommonErrors.hpp"

#include "Range.hpp"

#include <fmt/format.h>


namespace cmake::language
{
  tl::unexpected<Error> CreateEmptyRangeError(const Range& range, const std::string& expected)
  {
    Error error;
    error.message = fmt::format("Expected {}. Got empty range.", expected);
    error.context = range.begin;
    return tl::make_unexpected(error);
  }
}
