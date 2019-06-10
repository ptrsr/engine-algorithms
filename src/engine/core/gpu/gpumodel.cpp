#include "gpumodel.hpp"
#include <engine/input/model.hpp>


GpuModel::GpuModel(Model& model)
    : index_buffer_id(GenerateBuffer(model.indices, GL_ELEMENT_ARRAY_BUFFER))
    , vertex_buffer_id(GenerateBuffer(model.vertices, GL_ARRAY_BUFFER))
    , normal_buffer_id(GenerateBuffer(model.normals, GL_ARRAY_BUFFER))
    , uv_buffer_id(GenerateBuffer(model.uvs, GL_ARRAY_BUFFER)) 
    { }

GpuModel::GpuModel(std::unique_ptr<Model>& model)
    : GpuModel(*model.get())
    { }

void GpuModel::DeleteBuffer(const GLuint id) {
    // skip if buffer hasn't been instantiated
    if (id == 0) {
        return;
    }
    glDeleteBuffers(1, &id);
}

GpuModel::~GpuModel() {
    DeleteBuffer(index_buffer_id);
    DeleteBuffer(vertex_buffer_id);
    DeleteBuffer(normal_buffer_id);
    DeleteBuffer(uv_buffer_id);
}
