#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <engine/core/typemap.hpp>
#include <engine/core/system.hpp>
#include <engine/core/scene.hpp>

#include <engine/entities/profiler.hpp>

typedef std::unique_ptr<Scene> Scene_ptr;

class Engine : private TypeMap<System> {
public:
    Scene_ptr scene;

    Engine();
    virtual ~Engine();

    void Run(unsigned max_updates = 0);
    void Stop();

    template<typename T, class... P>
    T& AddSystem(P&&... p) {
        return AddBase<T>(std::forward<P>(p)...);
    }

    template<typename T>
    T* const GetSystem() {
        return GetBase<T>();
    }

protected:
    virtual void Update(UpdateContext& context);

private:
    bool running = false;
    
    Profiler& profiler;
};

typedef std::unique_ptr<Engine> Engine_ptr;

#endif//ENGINE_HPP_
