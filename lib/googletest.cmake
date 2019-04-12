cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)

ExternalProject_Add(googletest PREFIX googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.8.1

  UPDATE_COMMAND ""

  CMAKE_ARGS
    "-DINSTALL_GTEST=ON"
    "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
    "-DCMAKE_BUILD_TYPE=$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>"

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
