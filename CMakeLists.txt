cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_CXX_STANDARD 11) # Set C++ version to 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# setup libraries
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
include(glew)
include(glfw)
include(glm)
include(sfml)

include(googletest)

add_subdirectory(src)
