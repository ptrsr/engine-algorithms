#include "shader.hpp"

#include <vector>
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
    glDeleteShader(id);
}
