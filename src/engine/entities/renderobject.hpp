#ifndef RENDEROBJECT_HPP_
#define RENDEROBJECT_HPP_

#include <engine/entities/gameobject.hpp>

class Material;
class Mesh;

class RenderObject : public GameObject {
public:
    Material& material;
    Mesh& mesh;

    RenderObject(const unsigned id, std::shared_ptr<Material>& material, std::shared_ptr<Mesh>& mesh);

};

#endif//RENDEROBJECT_HPP_
