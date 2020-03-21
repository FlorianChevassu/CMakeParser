#pragma once

struct Error;
struct Range;

class ErrorPrinter
{
public:
  static void Print(const Range& i_script, const Error& err);
};
