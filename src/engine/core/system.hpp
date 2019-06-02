#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <memory>

class Scene;

struct UpdateContext {
    Scene& scene;
    const unsigned int microseconds;

    UpdateContext(Scene& scene, const unsigned int ms)
        : scene(scene)
        , microseconds(ms)
        { }
};

class Engine;

class System {
    friend class Engine;
    friend std::unique_ptr<System>::deleter_type;

public:
    bool enabled;
    virtual void Update(UpdateContext& scene) = 0;

};

#endif//SYSTEM_HPP_
