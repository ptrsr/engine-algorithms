#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <memory>

class Scene;

struct UpdateContext {
    Scene& scene;
    const unsigned microseconds;

    UpdateContext(Scene& scene, const unsigned ms)
        : scene(scene)
        , microseconds(ms)
        { }
};

class Engine;

class System {
public:
    bool enabled;
    virtual void Update(UpdateContext& scene) = 0;
    virtual void LateUpdate(UpdateContext& scene) { };

};

#endif//SYSTEM_HPP_
