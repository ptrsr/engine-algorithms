cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)

ExternalProject_Add(glfw PREFIX glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3

    TEST_COMMAND ""
    
    CMAKE_ARGS
        "-DCMAKE_BUILD_TYPE=$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>"
        "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
        
        "-DCMAKE_DEBUG_POSTFIX=d"
        "-DCMAKE_INSTALL_LIBDIR=lib" # https://cmake.org/cmake/help/v3.14/module/GNUInstallDirs.html
                                     # force libdir to be 'lib'. Otherwise it'll default to system arch (e.g. lib64)
        
        "-DBUILD_SHARED_LIBS=ON"
        "-DGLFW_BUILD_DOCS=OFF"
        "-DGLFW_BUILD_TESTS=OFF"
        "-DGLFW_BUILD_EXAMPLES=OFF"
        

    LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1 LOG_OUTPUT_ON_FAILURE 1
)

ExternalProject_Get_Property(glfw INSTALL_DIR)
set(GLFW_INCLUDE_DIR ${INSTALL_DIR}/include)
set(GLFW_LIBS
  ${INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}glfw$<$<CONFIG:Debug>:d>${CMAKE_SHARED_LIBRARY_SUFFIX}
)
