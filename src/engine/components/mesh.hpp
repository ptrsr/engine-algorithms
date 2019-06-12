#ifndef GPU_MODEL_HPP
#define GPU_MODEL_HPP

#include <memory>

#include <glbinding/gl/types.h>
#include <glbinding/gl/gl.h>

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

using namespace gl;

class Model;

class Mesh;
typedef std::shared_ptr<Mesh> Mesh_ptr;

class Mesh : public SharedComponent {
public:
    const GLuint index_buffer_id;
    const GLuint vertex_buffer_id;
    const GLuint normal_buffer_id;
    const GLuint uv_buffer_id;

    Mesh(Model& model);

    template <class ...Args>
    static Mesh_ptr Make(Args&& ...args) {
        return Mesh_ptr(new Mesh(std::forward<Args>(args)...));
    }

    template<typename T>
    GLuint GenerateBuffer(std::vector<T>& data, GLenum buffer_type) {
        GLuint id = 0;
        
        if (data.size() == 0) {
            return id;
        }
        glGenBuffers(1, &id);
        glBindBuffer(buffer_type, id);
        glBufferData(buffer_type, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
        return id;
    }

    void DeleteBuffer(const GLuint id);

    ~Mesh();

private:
    Mesh(const Mesh& copy) = default;

};

#endif//GPU_MODEL_HPP
