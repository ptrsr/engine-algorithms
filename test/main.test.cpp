#include <gtest/gtest.h>

#include <GLFW/glfw3.h>

#include <glbinding-aux/Meta.h>
#include <glbinding/AbstractFunction.h>
#include <glbinding-aux/ContextInfo.h>
#include <glbinding/Version.h>
#include <glbinding/glbinding.h>

#include <glbinding/gl/gl.h>

#include <glbinding-aux/ValidVersions.h>
#include <glbinding-aux/types_to_string.h>

#include <iostream>

// test resources
#ifndef TEST_RESOURCE_DIR
#define TEST_RESOURCE_DIR
#endif

int main(int argc, char** argv) {
#ifndef HEADLESS
    if (!glfwInit()) {
        std::cerr << "Could not init GLFW. Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, false);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(320, 240, "", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glbinding::initialize([](const char * name) {
        return glfwGetProcAddress(name);
    });
#endif

    testing::InitGoogleTest(&argc, argv);
    int status = RUN_ALL_TESTS();

#ifndef HEADLESS
    glfwDestroyWindow(window);
    glfwTerminate();
#endif

    return status;
}
