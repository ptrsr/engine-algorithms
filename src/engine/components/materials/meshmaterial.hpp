#ifndef MESH_MATERIAL_HPP_
#define MESH_MATERIAL_HPP_

#include <engine/components/material.hpp>

class Mesh;

class MeshMaterial : public Material {
public:
    // uniforms
    const GLint mvp_uniform;
    const GLint color_uniform;

    // attributes
    const GLint vertex_attribute;
    const GLint normal_attribute;
    const GLint uv_attribute;

    MeshMaterial(const std::string& file);
    bool Bind(Mesh& mesh);
    bool UnBind();

private:
    Mesh* bound_mesh = nullptr;
};

#endif//MESH_MATERIAL_HPP_
