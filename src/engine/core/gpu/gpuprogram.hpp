#ifndef GPUPROGRAM_HPP_
#define GPUPROGRAM_HPP_

#include <glbinding/gl/gl.h>
#include <memory>
#include <vector>
#include <string>

using namespace gl;

class Shader;
typedef std::shared_ptr<Shader> Shader_ptr;

class GpuProgram;
typedef std::shared_ptr<GpuProgram> GpuProgram_ptr;

class GpuProgram {
public:
    std::vector<Shader_ptr> shaders;
    const GLint id;

    template <class ...Args>
    static GpuProgram_ptr Make(Args&& ...args) {
        return GpuProgram_ptr(new GpuProgram(std::forward<Args>(args)...));
    }

    void Use();

    GLint GetUniform(const std::string& field) const;
    GLint GetAttribute(const std::string& field) const;

    ~GpuProgram();

private:
    GpuProgram(const GpuProgram& copy) = default;
    GpuProgram(const std::vector<Shader_ptr>& shaders);

};

#endif//GPUPROGRAM_HPP_
