#ifndef RENDEROBJECT_HPP_
#define RENDEROBJECT_HPP_

#include <engine/entities/gameobject.hpp>

class MeshMaterial;
class Mesh;

class RenderObject : public GameObject {
public:
    MeshMaterial& material;
    Mesh& mesh;
    bool visible = true;

    /* NOTE: will search for file.obj, file.vs and file.fs */
    RenderObject(const unsigned id, const std::string& file);
    RenderObject(const unsigned id, std::shared_ptr<MeshMaterial>& material, std::shared_ptr<Mesh>& mesh);
};

#endif//RENDEROBJECT_HPP_
