#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <engine/core/typemap.hpp>
#include <engine/core/system.hpp>
#include <engine/core/scene.hpp>

class Scene;
typedef std::unique_ptr<Scene> Scene_ptr;


struct Context {
    Scene& scene;
    const unsigned int microseconds;

    Context(Scene& scene, const unsigned int ms)
        : scene(scene)
        , microseconds(ms)
        { }
};

class Engine : protected TypeMap<System> {
private:
    bool running = false;

protected:
    virtual void Update();

public:
    Scene_ptr scene;

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

    template<typename T>
    void UpdateSystems(T context) {
        CheckType<Context, T>();

        for (auto& pair : *this) {
            pair.second->Update(context);
        }
    }
};

typedef std::unique_ptr<Engine> Engine_ptr;

#endif//ENGINE_HPP_
