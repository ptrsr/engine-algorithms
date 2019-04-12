cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)


ExternalProject_Add(glbinding PREFIX glbinding
    GIT_REPOSITORY https://github.com/cginternals/glbinding.git
    GIT_TAG v3.0.2

    UPDATE_COMMAND ""

    CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
        "-DCMAKE_BUILD_TYPE=$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>"
        "-DBUILD_SHARED_LIBS=OFF"
        "-DOPTION_BUILD_EXAMPLES=OFF"

    CMAKE_CACHE_ARGS
        "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}"
        "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"

    LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1 LOG_OUTPUT_ON_FAILURE 1
)

ExternalProject_Get_Property(glbinding INSTALL_DIR)
set(GLBINDING_INCLUDE_DIR ${INSTALL_DIR}/include)
set(GLBINDING_LIBS ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glbinding$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}) # not linking aux lib
