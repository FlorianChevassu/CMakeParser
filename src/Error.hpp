#pragma once
#include "Range.hpp"

#include <string>
#include <vector>

namespace cmake::language
{
  struct Error
  {
    Range context;
    std::string message;
    std::vector<Error> children;
  };
}
