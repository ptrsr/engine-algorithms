#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <engine/core/typemap.hpp>
#include <engine/core/system.hpp>
#include <engine/core/scene.hpp>

typedef std::unique_ptr<Scene> Scene_ptr;

class Engine : private TypeMap<System> {
private:
    bool running = false;

protected:
    virtual void Update(UpdateContext& context);

public:
    Scene_ptr scene;

    Engine();
    virtual ~Engine();

    void Run();
    void Stop();

    template<typename T, class... P>
    T& AddSystem(P&&... p) {
        return AddBase<T>(std::forward<P>(p)...);
    }

    template<typename T>
    T* const GetSystem() {
        return GetBase<T>();
    }
};

typedef std::unique_ptr<Engine> Engine_ptr;

#endif//ENGINE_HPP_
