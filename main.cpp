//========================================================================
// Simple GLFW example
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//! [code]

#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>

#include <engine/components/window.hpp>
#include <engine/components/material.hpp>
#include <engine/components/mesh.hpp>
#include <engine/glm.hpp>

#include <stdlib.h>
#include <stdio.h>

using namespace gl;

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    Window window = Window(nullptr, 300, 300, "test");

    std::vector<float> verts = { -0.6f, -0.4f, 1.f, 0.f, 0.f,
       0.6f, -0.4f, 0.f, 1.f, 0.f,
        0.f,  0.6f, 0.f, 0.f, 1.f };

    Buffer<float> buffer(verts, GL_ARRAY_BUFFER, 2, false);

    Shader_ptr vertex_shader = std::make_shared<Shader>(std::string(vertex_shader_text), Shader::vertex);
    Shader_ptr fragment_shader = std::make_shared<Shader>(std::string(fragment_shader_text), Shader::fragment);

    Shaders shaders = { vertex_shader, fragment_shader };
    Material material = Material(shaders);

    GLint mvp_location, vpos_location, vcol_location;
    mvp_location  = material.GetUniform("MVP");
    vpos_location = material.GetAttribute("vPos");
    vcol_location = material.GetAttribute("vCol");

    buffer.Bind(vpos_location, 2, sizeof(float) * 5);
    buffer.Bind(vcol_location, 3, sizeof(float) * 5, (void*) (sizeof(float) * 2));

    while (!glfwWindowShouldClose(window.context.get()))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window.context.get(), &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 m(1);
        
        material.Use();
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(m));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window.context.get());
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

//! [code]
