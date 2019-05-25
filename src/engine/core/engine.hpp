#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <engine/core/typecontainer.hpp>

class Scene;
typedef Scene_ptr std::unique_ptr<Scene>;

class System;
typedef System_ptr std::unique_ptr<System>;
typedef System_vec std::vector<System_ptr>;

class Engine : protected TypeContainer<System> {
protected:

    template<typename T, class... P>
    T& AddSystem(P&&... p) {
        return AddBase<T>(std::forward<P>(p)...);
    }

    template<typename T>
    T* const GetSystem() {
        return GetBase<T>();
    }

    void UpdateSystems();

public:

};

#endif//ENGINE_HPP_
