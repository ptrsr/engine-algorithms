cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)

set(CMAKE_INSTALL_LIBDIR lib)

ExternalProject_Add(googletest PREFIX googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.8.1

  UPDATE_COMMAND ""

  CMAKE_ARGS
    "-DINSTALL_GTEST=ON"
    "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
    "-DCMAKE_BUILD_TYPE=$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>"
    "-DCMAKE_INSTALL_LIBDIR=lib" # https://cmake.org/cmake/help/v3.14/module/GNUInstallDirs.html
                                 # force libdir to be 'lib'. Otherwise it'll default to system arch (e.g. lib64)
  CMAKE_CACHE_ARGS
    "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}"
    "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"

  LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1 LOG_OUTPUT_ON_FAILURE 1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ExternalProject_Get_Property(googletest INSTALL_DIR)

set(GOOGLETEST_INCLUDE_DIR ${INSTALL_DIR}/include)

set(GOOGLETEST_LIBS
  ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
)
