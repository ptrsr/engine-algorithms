#include "mesh.hpp"
#include <engine/input/model.hpp>
#include <stdexcept>

Mesh::Mesh(Model& model)
    : index_buffer (Buffer(model.indices, GL_ELEMENT_ARRAY_BUFFER, 1, false))
    , vertex_buffer(Buffer(model.vertices, GL_ARRAY_BUFFER, 3, false))
    , normal_buffer(Buffer(model.normals, GL_ARRAY_BUFFER, 3, true))
    , uv_buffer    (Buffer(model.uvs, GL_ARRAY_BUFFER, 2, false)) 
    { }
