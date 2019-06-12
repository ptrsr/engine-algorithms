#ifndef GPUPROGRAM_HPP_
#define GPUPROGRAM_HPP_

#include <memory>
#include <vector>
#include <string>

#include <glbinding/gl/gl.h>

#include <engine/core/component.hpp>

using namespace gl;

class Shader {
public:
    // will be casted to GLenum
    enum Type : unsigned int {
        vertex   = 0x8B31,
        fragment = 0x8B30
    };

    const GLuint id;
    const Type type;

    Shader(const Shader& copy) = default;
    Shader(const std::string& source, const Type type);
    
    ~Shader();
};

class Material : public SharedComponent {
public:
    const GLint id;

    Material(const Material& copy) = default;
    Material(const std::vector<Shader>& shaders);

    void Use();

    GLint GetUniform(const std::string& field) const;
    GLint GetAttribute(const std::string& field) const;

    ~Material();
};

#endif//GPUPROGRAM_HPP_
