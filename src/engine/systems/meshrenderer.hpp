#ifndef MESH_RENDERER_HPP_
#define MESH_RENDERER_HPP_

#include <engine/glm.hpp>

#include <engine/core/system.hpp>

class RenderObject;
class GameObject;
class Camera;

class MeshRenderer : public System {
public:
    bool wireframe = false;

    virtual void Update(UpdateContext& scene) override;
    virtual void Render(const RenderObject& object, const Camera& camera, const int mvp_id) const;

    glm::mat4 GetModelMatrix(GameObject& object) const;

};

#endif//MESH_RENDERER_HPP_
