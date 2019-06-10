#include "gpuprogram.hpp"

#include <stdexcept>
#include <iostream>

#include "engine/core/gpu/shader.hpp"

GpuProgram::GpuProgram(const std::vector<Shader_ptr>& shaders)
    : id(glCreateProgram())
    , shaders(shaders)
{
    for (const Shader_ptr& shader : shaders) {
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);

    GLboolean result = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &result);

    if (!result) {
        GLint info_length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_length);

        // get error message
        std::vector<char> error(info_length + 1);
        glGetProgramInfoLog(id, info_length, NULL, error.data());

        std::cerr << error.data() << std::endl;

        // throw with message
        throw new std::runtime_error(error.data());
    }
}

void GpuProgram::Use() {
    glUseProgram(id);
}

GLint GpuProgram::GetUniform(const std::string& field) const {
    return glGetUniformLocation(id, field.c_str());
}

GLint GpuProgram::GetAttribute(const std::string& field) const {
    return glGetAttribLocation(id, field.c_str());
}

GpuProgram::~GpuProgram() {
    glDeleteProgram(id);
}
