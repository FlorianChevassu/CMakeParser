ExternalProject_Add(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 6.1.2
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/fmt-install
    -DFMT_TEST:BOOL=OFF
)
set(fmt_DIR ${CMAKE_CURRENT_BINARY_DIR}/fmt-install/lib/cmake/fmt)