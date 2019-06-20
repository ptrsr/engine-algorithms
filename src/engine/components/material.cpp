#include "material.hpp"

#include <stdexcept>
#include <iostream>


Shader::Shader(const std::string& source, const Type type)
    : id(glCreateShader((GLenum)type))
    , type(type) 
{
    // add source and compile
    const char* source_ptr = source.c_str();
    glShaderSource(id, 1, &source_ptr, NULL);
    glCompileShader(id);

    // get compiling result
    GLboolean result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (!result) {
        // get error length
        int info_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_length);

        // get error message
        std::vector<char> error(info_length + 1);
        glGetShaderInfoLog(id, info_length, NULL, error.data());

        std::cerr << error.data() << std::endl;

        // throw with message
        throw new std::runtime_error(error.data());
    }
}

Shader::~Shader() {
    //glDeleteShader(id);
}

Material::Material(const Shaders& shaders)
    : id(glCreateProgram())
{
    for (const Shader_ptr shader : shaders) {
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

void Material::Use() {
    glUseProgram(id);
}

GLint Material::GetUniform(const std::string& field) const {
    return glGetUniformLocation(id, field.c_str());
}

GLint Material::GetAttribute(const std::string& field) const {
    return glGetAttribLocation(id, field.c_str());
}

Material::~Material() {
    //glDeleteProgram(id);
}
