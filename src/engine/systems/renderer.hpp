#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <engine/glm.hpp>

#include <engine/core/system.hpp>

class RenderObject;
class GameObject;
class Camera;

class Renderer : public System {
public:
    Renderer();
    virtual void Update(UpdateContext& scene) override;
    virtual void LateUpdate(UpdateContext& scene) override;
    virtual void Render(const RenderObject& object, const Camera& camera, const int mvp_id) const;

    glm::mat4 GetModelMatrix(GameObject& object) const;


};

#endif//RENDERER_HPP_
