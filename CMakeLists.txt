cmake_minimum_required(VERSION 3.0)

project(engine-algorithms 
    VERSION 0.0.1 
)

# Set C++ version to 11
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# executable output folder
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

# setup libraries
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/)

# set parallel build for MSVC
if(MSVC)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# dependencies
include(glbinding)
include(glm)
include(sfml)

# testing framework
include(googletest)

# build project
add_subdirectory(src/)

# build tests
option(BUILD_TESTS "Build tests" ON)
if (${BUILD_TESTS})
    add_subdirectory(test/)
endif()

