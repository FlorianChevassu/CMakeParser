cmake_minimum_required(VERSION 3.14)

project(CMakeParser LANGUAGES CXX)

option(STRICT_MODE "Make sure the parser strictly match the CMake documentation" OFF)
add_subdirectory(src)

option(BUILD_TESTING "Build tests" ON)
if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
