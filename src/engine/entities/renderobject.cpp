#include "renderobject.hpp"

#include <engine/components/material.hpp>
#include <engine/components/mesh.hpp>

RenderObject::RenderObject(const unsigned id, std::shared_ptr<Material>& material, std::shared_ptr<Mesh>& mesh)
    : GameObject(id)
    , material(AddComponent(material))
    , mesh(AddComponent(mesh))
    { }
