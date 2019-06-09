#include "gpumodel.hpp"
#include <engine/input/model.hpp>


GpuModel::GpuModel(Model& model)
    : index_buffer_id(GenerateBuffer(model.indices, gl::GL_ELEMENT_ARRAY_BUFFER))
    , vertex_buffer_id(GenerateBuffer(model.vertices, gl::GL_ARRAY_BUFFER))
    , normal_buffer_id(GenerateBuffer(model.normals, gl::GL_ARRAY_BUFFER))
    , uv_buffer_id(GenerateBuffer(model.uvs, gl::GL_ARRAY_BUFFER)) 
    { }

GpuModel::GpuModel(std::unique_ptr<Model>& model)
    : GpuModel(*model.get())
    { }
