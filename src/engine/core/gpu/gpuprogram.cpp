#include "gpuprogram.hpp"

#include <stdexcept>
#include <iostream>

#include "engine/core/gpu/shader.hpp"


GpuProgram::GpuProgram(const std::vector<Shader_ptr>& shaders)
    : id(gl::glCreateProgram())
    , shaders(shaders)
{
    for (const Shader_ptr& shader : shaders) {
        gl::glAttachShader(id, shader->id);
    }
    gl::glLinkProgram(id);

    gl::GLboolean result = gl::GL_FALSE;
    gl::glGetProgramiv(id, gl::GL_LINK_STATUS, &result);

    if (!result) {
        gl::GLint info_length;
        glGetProgramiv(id, gl::GL_INFO_LOG_LENGTH, &info_length);

        // get error message
        std::vector<char> error(info_length + 1);
        gl::glGetProgramInfoLog(id, info_length, NULL, error.data());

        std::cerr << error.data() << std::endl;

        // throw with message
        throw new std::runtime_error(error.data());
    }
}
