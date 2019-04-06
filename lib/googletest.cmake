cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)

ExternalProject_Add(googletest PREFIX googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.8.1

  UPDATE_COMMAND ""

  CMAKE_ARGS
    "-DINSTALL_GTEST=OFF"

  CMAKE_CACHE_ARGS
    "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}"
    "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"

  # copy include directories to install dir
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory 
    <SOURCE_DIR>/googletest/include/ <INSTALL_DIR>/include/
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
    <SOURCE_DIR>/googlemock/include/ <INSTALL_DIR>/include/

  # create a new lib directory
  COMMAND ${CMAKE_COMMAND} -E make_directory <INSTALL_DIR>/lib/
  
  # copy libs
  COMMAND ${CMAKE_COMMAND} -E copy 
    <BINARY_DIR>/googlemock/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX} 
    <INSTALL_DIR>/lib/
  COMMAND ${CMAKE_COMMAND} -E copy 
    <BINARY_DIR>/googlemock/gtest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
    <INSTALL_DIR>/lib/

  LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ExternalProject_Get_Property(googletest INSTALL_DIR)

set(GOOGLETEST_INCLUDE_DIR ${INSTALL_DIR}/include)

set(GOOGLETEST_LIBS
  ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
)

set(GOOGLETEST_INCLUDE_DIRS ${GOOGLETEST_INCLUDE_DIRS} CACHE STRING "")
set(GOOGLETEST_LIBS ${GOOGLETEST_LIBS} CACHE STRING "")
