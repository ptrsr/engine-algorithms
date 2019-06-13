#include "mesh.hpp"
#include <engine/input/model.hpp>
#include <stdexcept>


template<typename Base>
GLuint Buffer<Base>::GenBuffer() {
        GLuint id = 0;
        glGenBuffers(1, &id);
        return id;
}

template<typename Base>
bool Buffer<Base>::Bind(GLint attribute_id) {
    if (attribute_id == -1) {
        return false;
    }

    glBindBuffer(type, attribute_id);

    // no need to bind attributes on indices
    if (type == GL_ELEMENT_ARRAY_BUFFER) {
        return true;
    }
    glEnableVertexAttribArray(attribute_id);
    glVertexAttribPointer(attribute_id, rows, GL_FLOAT, stride, 0, 0);

    return true;
}

template<typename Base>
Buffer<Base>::~Buffer() {
    if (id == 0) {
        return;
    }
    glDeleteBuffers(1, &id);
}

Mesh::Mesh(Model& model)
    : index_buffer (Buffer(model.indices, GL_ELEMENT_ARRAY_BUFFER, 1, false))
    , vertex_buffer(Buffer(model.vertices, GL_ARRAY_BUFFER, 3, false))
    , normal_buffer(Buffer(model.normals, GL_ARRAY_BUFFER, 3, true))
    , uv_buffer    (Buffer(model.uvs, GL_ARRAY_BUFFER, 2, false)) 
    { }
