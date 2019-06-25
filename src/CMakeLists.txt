cmake_minimum_required(VERSION 3.0)

## INCLUDING
# headers
include_directories(./)

# dependency headers
include_directories(${GLM_INCLUDE_DIR})

# define where resources are located
add_definitions(-DRESOURCE_DIR="${PROJECT_SOURCE_DIR}/resources/")

# build engine library
add_subdirectory(engine)

if(${BUILD_HEAD})
    # build game executable
    add_subdirectory(game)
endif()
