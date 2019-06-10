#ifndef GPUPROGRAM_HPP_
#define GPUPROGRAM_HPP_

#include <glbinding/gl/gl.h>
#include <memory>
#include <vector>

class Shader;
typedef std::shared_ptr<Shader> Shader_ptr;

class GpuProgram {
public:
    std::vector<Shader_ptr> shaders;
    const gl::GLint id;

    GpuProgram(const std::vector<Shader_ptr>& shaders);
};

#endif//GPUPROGRAM_HPP_
