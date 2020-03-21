#include "ErrorPrinter.hpp"

#include "Tokenizer/Tokenizer.hpp"

#include <iostream>

void PrintContextPrefix(const Range& i_script, const It& i_it)
{
  Context ctx = i_script.GetContext(i_it);
  std::cout << ctx.line << ", " << ctx.column << " : ";
}

void ErrorPrinter::Print(const Range& i_script, const Error& i_error)
{
  Context begin = i_script.GetContext(i_error.context.begin);
  Context end = i_script.GetContext(i_error.context.end);

  PrintContextPrefix(i_script, i_error.context.begin);
  std::cout << i_error.message << '\n';
  for (auto& child : i_error.children)
  {
    PrintContextPrefix(i_script, child.context.begin);
    std::cout << "\t" << child.message << '\n';
  }
}