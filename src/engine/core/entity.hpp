#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>
#include <engine/core/typemap.hpp>

class Scene;

class Entity : protected TypeMap<Component> {
    friend Scene;

private:
    std::vector<std::type_index> type_register;

    // copy constructor
    Entity(const Entity& original, const unsigned int new_id)
        : id(new_id)
        , TypeMap<Component>(original)
        { }

protected:
    Entity(const unsigned int id = 0)
        : id(id)
        { }

    virtual void OnRegister(Scene& scene) { }

    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        return AddBase<T>(std::forward<P>(p)..., this);
    }

public:
    // proper deletion by Entity pointer
    virtual ~Entity() = default;

    const unsigned int id;

    template<typename T>
    T* const GetComponent() {
        return GetBase<T>();
    }
};

#endif//ENTITY_HPP_
