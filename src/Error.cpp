#include "Error.hpp"

namespace cmake::language
{
  ErrorBuilder Error::make()
  {
    return ErrorBuilder();
  }

  ErrorBuilder& ErrorBuilder::context(const Range& context)
  {
    error.context = context;
    return *this;
  }

  ErrorBuilder& ErrorBuilder::message(const std::string& message)
  {
    error.message = message;
    return *this;
  }

  ErrorBuilder& ErrorBuilder::children(const std::vector<Error>& children)
  {
    error.children = children;
    return *this;
  }

  ErrorBuilder::operator Error&&()
  {
    return std::move(error);
  }
}