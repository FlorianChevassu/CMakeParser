ExternalProject_Add(expected
  GIT_REPOSITORY https://github.com/TartanLlama/expected.git
  GIT_TAG v1.0.0
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/expected-install
    -DEXPECTED_BUILD_TESTS:BOOL=OFF
)
set(tl-expected_DIR ${CMAKE_CURRENT_BINARY_DIR}/expected-install/share/cmake/tl-expected)