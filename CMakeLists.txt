
cmake_minimum_required(VERSION 2.8.2)
message(${CMAKE_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
include(glew)
include(glfw)
include(googletest)
