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

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/ArgumentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ArgumentsParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BracketArgumentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BracketCloseParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BracketCommentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BracketContentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BracketOpenParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CommandInvocationParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ElementType.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Error.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EscapeEncodedParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EscapeIdentityParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EscapeSemiliconParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EscapeSequenceParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileElementParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FileParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IdentifierParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LineCommentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LineEndingParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NewLineParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QuotedArgumentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QuotedContinuationParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QuotedElementParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Range.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SeparatedArgumentsParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SeparationParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SpaceParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Token.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UnquotedArgumentParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UnquotedElementParser.hpp)

target_sources(CMakeParser PRIVATE ${HEADERS}
    ArgumentParser.cpp
    ArgumentsParser.cpp
    BracketArgumentParser.cpp
    BracketCloseParser.cpp
    BracketCommentParser.cpp
    BracketContentParser.cpp
    BracketOpenParser.cpp
    CommandInvocationParser.cpp
    EscapeEncodedParser.cpp
    EscapeIdentityParser.cpp
    EscapeSemiliconParser.cpp
    EscapeSequenceParser.cpp
    FileElementParser.cpp
    FileParser.cpp
    IdentifierParser.cpp
    LineCommentParser.cpp
    LineEndingParser.cpp
    NewLineParser.cpp
    QuotedArgumentParser.cpp
    QuotedContinuationParser.cpp
    QuotedElementParser.cpp
    Range.cpp
    SeparatedArgumentsParser.cpp
    SeparationParser.cpp
    SpaceParser.cpp
    UnquotedArgumentParser.cpp
    UnquotedElementParser.cpp
)


set_target_properties(CMakeParser PROPERTIES PUBLIC_HEADER "${HEADERS}")
