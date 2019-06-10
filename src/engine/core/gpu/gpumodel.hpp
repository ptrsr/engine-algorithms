#ifndef GPU_MODEL_HPP
#define GPU_MODEL_HPP

#include <memory>
#include <glbinding/gl/types.h>
#include <glbinding/gl/gl.h>

#include <engine/glm.hpp>

class Model;

class GpuModel {
public:
    const gl::GLuint index_buffer_id;
    const gl::GLuint vertex_buffer_id;
    const gl::GLuint normal_buffer_id;
    const gl::GLuint uv_buffer_id;

    GpuModel(Model& model);
    GpuModel(std::unique_ptr<Model>& model);

    template<typename T>
    gl::GLuint GenerateBuffer(std::vector<T>& data, gl::GLenum buffer_type) {
        gl::GLuint id = 0;
        // no buffer created when there is no data to put into it
        if (data.size() == 0) {
            return id;
        }
        gl::glGenBuffers(1, &id);
        gl::glBindBuffer(buffer_type, id);
        gl::glBufferData(buffer_type, data.size() * sizeof(T), &data[0], gl::GL_STATIC_DRAW);
        return id;
    }
};

#endif//GPU_MODEL_HPP
