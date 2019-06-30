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
    virtual void Start(Scene& scene) { }
    virtual void Update(UpdateContext& scene) = 0;

};

#endif//SYSTEM_HPP_
