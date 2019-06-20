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
    enum Type : unsigned {
        vertex   = 0x8B31,
        fragment = 0x8B30
    };

    const GLuint id;
    const Type type;

    Shader(const std::string& source, const Type type);
    ~Shader();

private:
    Shader(const Shader& copy) = default;
};

typedef std::shared_ptr<Shader> Shader_ptr;
typedef std::vector<Shader_ptr> Shaders;

class Material : public SharedComponent {
public:
    const GLint id;

    Material(const Material& copy) = default;
    Material(const Shaders& shaders);

    void Use();

    GLint GetUniform(const std::string& field) const;
    GLint GetAttribute(const std::string& field) const;

    ~Material();
};

typedef std::shared_ptr<Material> Material_ptr;

#endif//GPUPROGRAM_HPP_
