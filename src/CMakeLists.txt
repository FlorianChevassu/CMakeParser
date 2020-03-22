find_package(fmt REQUIRED)
find_package(tl-expected REQUIRED)

add_library(CMakeParser)

target_link_libraries(CMakeParser
    PRIVATE fmt::fmt
    PUBLIC tl::expected
)

target_include_directories(CMakeParser
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<INSTALL_INTERFACE:include>
)

target_compile_features(CMakeParser PUBLIC cxx_std_17)

if(STRICT_MODE)
  target_compile_definitions(CMakeParser PUBLIC CMAKE_PARSER_STRICT_MODE)
endif()

target_sources(CMakeParser PRIVATE
    ArgumentParser.hpp
    ArgumentParser.cpp
    ArgumentsParser.hpp
    ArgumentsParser.cpp
    BracketArgumentParser.hpp
    BracketArgumentParser.cpp
    BracketCloseParser.hpp
    BracketCloseParser.cpp
    BracketCommentParser.hpp
    BracketCommentParser.cpp
    BracketContentParser.hpp
    BracketContentParser.cpp
    BracketOpenParser.hpp
    BracketOpenParser.cpp
    CommandInvocationParser.hpp
    CommandInvocationParser.cpp
    ElementType.hpp
    Error.hpp
    EscapeEncodedParser.hpp
    EscapeEncodedParser.cpp
    EscapeIdentityParser.hpp
    EscapeIdentityParser.cpp
    EscapeSemiliconParser.hpp
    EscapeSemiliconParser.cpp
    EscapeSequenceParser.hpp
    EscapeSequenceParser.cpp
    FileElementParser.hpp
    FileElementParser.cpp
    FileParser.hpp
    FileParser.cpp
    IdentifierParser.hpp
    IdentifierParser.cpp
    LineCommentParser.hpp
    LineCommentParser.cpp
    LineEndingParser.hpp
    LineEndingParser.cpp
    NewLineParser.hpp
    NewLineParser.cpp
    Parser.hpp
    QuotedArgumentParser.hpp
    QuotedArgumentParser.cpp
    QuotedContinuationParser.hpp
    QuotedContinuationParser.cpp
    QuotedElementParser.hpp
    QuotedElementParser.cpp
    Range.hpp
    Range.cpp
    SeparatedArgumentsParser.hpp
    SeparatedArgumentsParser.cpp
    SeparationParser.hpp
    SeparationParser.cpp
    SpaceParser.hpp
    SpaceParser.cpp
    Token.hpp
    UnquotedArgumentParser.hpp
    UnquotedArgumentParser.cpp
    UnquotedElementParser.hpp
    UnquotedElementParser.cpp
)
