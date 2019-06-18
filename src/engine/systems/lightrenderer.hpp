#ifndef LIGHT_RENDERER_HPP_
#define LIGHT_RENDERER_HPP_

#include <engine/systems/renderer.hpp>

class LightRenderer : public Renderer {
    virtual void Update(UpdateContext& scene) override;

};

#endif//LIGHT_RENDERER_HPP_
