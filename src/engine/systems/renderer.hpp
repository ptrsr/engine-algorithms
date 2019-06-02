#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <engine/core/system.hpp>

class Renderer : public System {
public:
    virtual void Update(UpdateContext& scene) override;

};

#endif//RENDERER_HPP_
