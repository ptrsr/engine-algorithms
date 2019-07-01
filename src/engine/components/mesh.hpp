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
private:
    GLint bound = -1;
  
    GLuint GenBuffer() {
        GLuint id = 0;
        glGenBuffers(1, &id);
        return id;
    };
    
public:
    const GLuint id = 0;
    const GLenum type;
    
    const unsigned rows;
    const unsigned size;
    const bool normalized;

    Buffer(std::vector<Base>& data, GLenum type, const unsigned rows, const bool normalized)
        : rows(rows)
        , normalized(normalized)
        , type(type)
        , size(data.size())
        , id(data.size() ? GenBuffer() : 0) 
    {
        if (id == 0) {
            return;
        }

        glBindBuffer(type, id);
        glBufferData(type, data.size() * sizeof(Base), &data[0], GL_STATIC_DRAW);
    }

    bool Bind(const GLint attribute_id = -1, const unsigned alt_rows = 0, const GLsizei stride = 0, const void* offset = 0) {
        if (id == 0) {
            return false;
        }

        // no need to bind attributes on indices
        if (type == GL_ELEMENT_ARRAY_BUFFER) {
            glBindBuffer(type, id);
            return true;
        } else if (attribute_id == -1) {
            // should bind to valid attribute
            return false;
        }
       
        glBindBuffer(type, id);

        bound = attribute_id;
        glEnableVertexAttribArray(attribute_id);
        glVertexAttribPointer(attribute_id, alt_rows ? alt_rows : rows, GL_FLOAT, normalized, stride, offset);
        return true;
    }

    bool UnBind() {
        if (bound == -1) {
            return false;
        }

        // no need to unbind attributes on indices
        if (type == GL_ELEMENT_ARRAY_BUFFER) {
            return false;
        }

        glDisableVertexAttribArray(bound);
        bound = -1;
        return true;
    }

    ~Buffer() {
        if (id == 0) {
            return;
        }
        glDeleteBuffers(1, &id);
    }
};


class Model;
typedef std::shared_ptr<Model> Model_ptr;

class Mesh : public SharedComponent {
public:
    Buffer<unsigned>  index_buffer;
    Buffer<glm::vec3> vertex_buffer;
    Buffer<glm::vec3> normal_buffer;
    Buffer<glm::vec2> uv_buffer;

    Mesh(const Model_ptr model);
    Mesh(const std::string& file);

private:
    Mesh(const Mesh& copy) = default;

};

typedef std::shared_ptr<Mesh> Mesh_ptr;

#endif//GPU_MODEL_HPP
