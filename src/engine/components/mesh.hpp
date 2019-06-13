#ifndef GPU_MODEL_HPP
#define GPU_MODEL_HPP

#include <memory>

#include <glbinding/gl/types.h>
#include <glbinding/gl/gl.h>

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

using namespace gl;

template<class Base>
class Buffer {
public:
    const GLuint id = 0;
    const GLenum type;
    
    const unsigned rows;
    const bool stride;

    Buffer(std::vector<Base>& data, GLenum type, const unsigned rows, const bool stride)
        : rows(rows)
        , stride(stride)
        , type(type)
        , id(data.size() ? GenBuffer() : 0) 
    {
        if (id == 0) {
            return;
        }

        glBindBuffer(type, id);
        glBufferData(type, data.size() * sizeof(Base), &data[0], GL_STATIC_DRAW);
    }
    
    ~Buffer();

    bool Bind(GLint attribute_id);

private:
    GLuint GenBuffer();
};


class Model;

class Mesh : public SharedComponent {
public:
    const Buffer<unsigned>  index_buffer;
    const Buffer<glm::vec3> vertex_buffer;
    const Buffer<glm::vec3> normal_buffer;
    const Buffer<glm::vec2> uv_buffer;

    Mesh(Model& model);

private:
    Mesh(const Mesh& copy) = default;

};

typedef std::shared_ptr<Mesh> Mesh_ptr;

#endif//GPU_MODEL_HPP
