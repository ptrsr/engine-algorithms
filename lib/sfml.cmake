cmake_minimum_required(VERSION 2.8.2)
include(ExternalProject)

ExternalProject_Add(sfml PREFIX sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1

    UPDATE_COMMAND ""

    CMAKE_ARGS
        "-DCMAKE_BUILD_TYPE=$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>"
        "-DBUILD_SHARED_LIBS=FALSE"
        "-DSFML_BUILD_AUDIO=FALSE"
        "-DSFML_BUILD_NETWORK=FALSE"
        "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"

        "-DSFML_BUILD_WINDOW=${BUILD_HEAD}"
        "-DSFML_BUILD_GRAPHICS=${BUILD_HEAD}"

    LOG_DOWNLOAD 1 LOG_UPDATE 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1 LOG_OUTPUT_ON_FAILURE 1
)

ExternalProject_Get_Property(sfml INSTALL_DIR)
set(SFML_INCLUDE_DIR ${INSTALL_DIR}/include)

set(SFML_LIBS ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sfml-system-s$<$<CONFIG:Debug>:-d>${CMAKE_STATIC_LIBRARY_SUFFIX})

if (${BUILD_HEAD})
    list(APPEND SFML_LIBS 
        ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sfml-graphics-s$<$<CONFIG:Debug>:-d>${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sfml-window-s$<$<CONFIG:Debug>:-d>${CMAKE_STATIC_LIBRARY_SUFFIX}
    )

    if (UNIX)
        find_package(X11 REQUIRED)

        set(OpenGL_GL_PREFERENCE "LEGACY")
        find_package(OpenGL REQUIRED)

        find_package(UDEV REQUIRED)

        message("FOUND: ${UDEV_FOUND}")

        list(APPEND SFML_INCLUDE_DIR ${X11_INCLUDE_DIR})

        list(APPEND SFML_LIBS
            ${X11_LIBRARIES}
            X11::Xrandr
            OpenGL::GL
        )
    endif()
endif()
