cmake_minimum_required(VERSION 3.14)

project(CMakeParser LANGUAGES CXX)

option(BUILD_SUPERBUILD "Build CMakeParser using the Superbuild." ON)
if(BUILD_SUPERBUILD)
  include(cmake/Superbuild.cmake)
  return()
endif()

option(STRICT_MODE "Make sure the parser strictly match the CMake documentation" OFF)
add_subdirectory(src)

option(BUILD_TESTING "Build tests" ON)
if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

export(TARGETS CMakeParser NAMESPACE CMakeParser:: FILE CMakeParserTargets.cmake)

install(TARGETS CMakeParser
        EXPORT CMakeParserTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        INCLUDES DESTINATION include
)

install(EXPORT CMakeParserTargets
        FILE CMakeParserTargets.cmake
        NAMESPACE CMakeParser::
        DESTINATION lib/cmake/CMakeParser
)

configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeParserConfig.cmake.in CMakeParserConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeParserConfig.cmake"
        DESTINATION lib/cmake/CMakeParser
)
