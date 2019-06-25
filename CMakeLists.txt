cmake_minimum_required(VERSION 3.0)

project(engine-algorithms VERSION 0.0.1)

# options
option(BUILD_HEAD "Build with graphics" ON)
option(BUILD_TESTS "Build tests" ON)


# force C++17
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_BUILD_TYPE)
	# capitalizing first character to avoid confusion
	string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
	string(SUBSTRING "${CMAKE_BUILD_TYPE}" 0 1 FIRST_CHARACTER)
	string(SUBSTRING "${CMAKE_BUILD_TYPE}" 1 -1 LAST_CHARACTER)
	string(TOUPPER ${FIRST_CHARACTER} FIRST_CHARACTER)
    string(CONCAT CMAKE_BUILD_TYPE ${FIRST_CHARACTER} ${LAST_CHARACTER})
else()
    # default
    set(CMAKE_BUILD_TYPE Debug)
endif()

# include lib directory for importing (library) modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/lib/)


# visual studio
if(MSVC)
    # set parallel build for MSVC
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
    
    # some neccessary compiler flags
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()


# dependencies
include(glm)

if(${BUILD_HEAD})
    include(glbinding)
    include(glfw)

    # header files
    include_directories(
        ${GLBINDING_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
    )
else()
    # preprocessor variable for headless (testing)
    add_compile_options("-DHEADLESS")
endif()


# preprocessor variable for debugging
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.13.0")
	# policy for converting local to global paths in target_sources
	cmake_policy(SET CMP0076 OLD)
endif()


# build project
add_subdirectory(src/)


# build tests
if (${BUILD_TESTS})
    # testing framework
    include(googletest)
    
    # test project
    add_subdirectory(test/)
endif()


# build overview
message("
### ENGINE ALGORITHMS
- Build : ${CMAKE_BUILD_TYPE}
- Tests : ${BUILD_TESTS}
- Head  : ${BUILD_HEAD}
###
")
