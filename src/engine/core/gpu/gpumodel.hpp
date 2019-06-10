#ifndef GPU_MODEL_HPP
#define GPU_MODEL_HPP

#include <memory>
#include <glbinding/gl/types.h>
#include <glbinding/gl/gl.h>

#include <engine/glm.hpp>

using namespace gl;

class Model;

class GpuModel;
typedef std::shared_ptr<GpuModel> GpuModel_ptr;

class GpuModel {
public:
    const GLuint index_buffer_id;
    const GLuint vertex_buffer_id;
    const GLuint normal_buffer_id;
    const GLuint uv_buffer_id;

    template <class ...Args>
    static GpuModel_ptr Make(Args&& ...args) {
        return GpuModel_ptr(new GpuModel(std::forward<Args>(args)...));
    }

    template<typename T>
    GLuint GenerateBuffer(std::vector<T>& data, GLenum buffer_type) {
        GLuint id = 0;
        // no buffer created when there is no data to put into it
        if (data.size() == 0) {
            return id;
        }
        glGenBuffers(1, &id);
        glBindBuffer(buffer_type, id);
        glBufferData(buffer_type, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
        return id;
    }

    void DeleteBuffer(const GLuint id);

    ~GpuModel();

private:
    GpuModel(Model& model);
    GpuModel(std::unique_ptr<Model>& model);
    GpuModel(const GpuModel& copy) = default;

};

#endif//GPU_MODEL_HPP
