cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)

ExternalProject_Add(glm PREFIX glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.5
    
    CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"

    TEST_COMMAND      ""

    LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1
)

ExternalProject_Get_Property(glm INSTALL_DIR)
set(GLM_INCLUDE_DIR ${INSTALL_DIR}/include)
