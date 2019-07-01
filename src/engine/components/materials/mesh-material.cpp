#include "mesh-material.hpp"

#include <engine/components/mesh.hpp>

MeshMaterial::MeshMaterial(const std::string& file)    
    : Material(file)
    , mvp_uniform(GetUniform("mvp"))
    , color_uniform(GetUniform("color"))
    , vertex_attribute(GetAttribute("vertex"))
    , normal_attribute(GetAttribute("normal"))
    , uv_attribute(GetAttribute("uv")) 
    { }

bool MeshMaterial::Bind(Mesh& mesh) {
    bool bound = mesh.index_buffer.Bind()
               | mesh.vertex_buffer.Bind(vertex_attribute)
               | mesh.normal_buffer.Bind(normal_attribute)
               | mesh.uv_buffer.Bind(uv_attribute);

    if (bound) {
        bound_mesh = &mesh;
    }
    return bound;
}

bool MeshMaterial::UnBind() {
    if (!bound_mesh) {
        return false;
    }
    bool unbound = bound_mesh->vertex_buffer.UnBind()
         | bound_mesh->normal_buffer.UnBind()
         | bound_mesh->uv_buffer.UnBind();
    
    bound_mesh = nullptr;
    return unbound;
}
