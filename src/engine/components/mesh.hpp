#ifndef GPU_MODEL_HPP
#define GPU_MODEL_HPP

#include <memory>

#include <glbinding/gl/types.h>
#include <glbinding/gl/gl.h>

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

#include <iostream>

using namespace gl;

template<class Base>
class Buffer {
public:
    const GLuint id = 0;
    const GLenum type;
    
    const unsigned rows;
    const unsigned size;
    const bool stride;

    Buffer(std::vector<Base>& data, GLenum type, const unsigned rows, const bool stride)
        : rows(rows)
        , stride(stride)
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

    bool Bind(const GLint attribute_id) {
        if (attribute_id == -1) {
            return false;
        }
        glBindBuffer(type, id);


        std::cout << "atrib: " << attribute_id << ", buffer: " << id << std::endl;

        // no need to bind attributes on indices
        if (type == GL_ELEMENT_ARRAY_BUFFER) {
            return true;
        }
        // save bound attribute
        bound = attribute_id;
        glEnableVertexAttribArray(attribute_id);
        glVertexAttribPointer(attribute_id, rows, GL_FLOAT, stride, 0, 0);
        return true;
    }

    bool UnBind() {
        if (bound == -1) {
            return false;
        }
        glDisableVertexAttribArray(bound);
        return true;
    }

    ~Buffer() {
        if (id == 0) {
            return;
        }
        glDeleteBuffers(1, &id);
    }

private:
    GLint bound = -1;
  
    GLuint GenBuffer() {
        GLuint id = 0;
        glGenBuffers(1, &id);
        return id;
    };
};


class Model;

class Mesh : public SharedComponent {
public:
    Buffer<unsigned>  index_buffer;
    Buffer<glm::vec3> vertex_buffer;
    Buffer<glm::vec3> normal_buffer;
    Buffer<glm::vec2> uv_buffer;

    Mesh(Model& model);

private:
    Mesh(const Mesh& copy) = default;

};

typedef std::shared_ptr<Mesh> Mesh_ptr;

#endif//GPU_MODEL_HPP
