#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <glbinding/gl/gl.h>

class Shader {
public:
    // will be casted to gl::GLenum
    enum Type : unsigned int {
        vertex   = 0x8B31,
        fragment = 0x8B30
    };

    Shader(std::string source, Type type);
};

#endif//SHADER_HPP_
