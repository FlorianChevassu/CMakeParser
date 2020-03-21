#pragma once

namespace cmake::language
{
  enum class ElementType
  {
    Argument,
    Arguments,
    BracketArgument,
    BracketClose,
    BracketComment,
    BracketContent,
    BracketOpen,
    CommandInvocation,
    EscapeEncoded,
    EscapeIdentity,
    EscapeSemilicon,
    EscapeSequence,
    File,
    FileElement,
    Identifier,
    LineComment,
    LineEnding,
    NewLine,
    QuotedArgument,
    QuotedContinuation,
    QuotedElement,
    SeparatedArguments,
    Separation,
    Space,
    UnquotedArgument,
    UnquotedElement
  };

}
