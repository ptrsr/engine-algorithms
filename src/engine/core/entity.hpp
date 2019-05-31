#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>
#include <engine/core/typemap.hpp>

class Entity : protected TypeMap<Component> {
    friend class Scene;
    friend std::unique_ptr<Entity>::deleter_type;

private:
    // copy constructor
    Entity(const Entity& original, const unsigned int new_id)
        : id(new_id)
        , TypeMap<Component>(original)
        { }

protected:
    Entity(const unsigned int id = 0)
        : id(id)
        { }

    // prohibit manual deletion
    virtual ~Entity() = default;
    void operator delete(void*) { }

    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        return AddBase<T>(std::forward<P>(p)..., this);
    }

public:
    const unsigned int id;

    template<typename T>
    T* const GetComponent() {
        return GetBase<T>();
    }
};

#endif//ENTITY_HPP_
