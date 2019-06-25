#include "renderobject.hpp"

#include <engine/input/file.hpp>

#include <engine/components/materials/meshmaterial.hpp>
#include <engine/components/mesh.hpp>


RenderObject::RenderObject(const unsigned id, std::shared_ptr<MeshMaterial>& material, Mesh_ptr& mesh)
    : GameObject(id)
    , material(AddComponent(material))
    , mesh(AddComponent(mesh))
    { }


RenderObject::RenderObject(const unsigned id, const std::string& file)
    : GameObject(id)
    , material(AddComponent(SharedComponent::Make<MeshMaterial>(file)))
    , mesh(AddComponent(SharedComponent::Make<Mesh>(file))) 
    { }
