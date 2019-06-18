#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <engine/core/system.hpp>

class RenderObject;
class Camera;

class Renderer : public System {
public:
    Renderer();
    ~Renderer();
    virtual void Update(UpdateContext& scene) override;
    virtual void Render(const RenderObject& object, const Camera& camera, const int mvp_id) const;

};

#endif//RENDERER_HPP_
