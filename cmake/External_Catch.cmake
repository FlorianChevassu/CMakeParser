ExternalProject_Add(Catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.11.1
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/catch2-install
    -DBUILD_TESTING:BOOL=OFF
)
set(Catch2_DIR ${CMAKE_CURRENT_BINARY_DIR}/catch2-install/lib/cmake/Catch2)