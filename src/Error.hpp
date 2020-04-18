#pragma once
#include "Range.hpp"

#include <string>
#include <vector>

namespace cmake::language
{
  struct ErrorBuilder;

  struct Error
  {
    static ErrorBuilder make();

    Range context;
    std::string message;
    std::vector<Error> children;
  };

  struct ErrorBuilder
  {
    ErrorBuilder& context(const Range& range);
    ErrorBuilder& message(const std::string& message);
    ErrorBuilder& children(const std::vector<Error>& children);

    operator Error&&();

  private:
    Error error;
  };
}
