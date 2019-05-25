#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>
#include <engine/core/typecontainer.hpp>

class Entity : protected TypeContainer<Component> {
    friend class Scene;
    friend std::unique_ptr<Entity>::deleter_type;
    typedef std::map<std::type_index, Component_ptr> Components;

private:
    // copy constructor
    Entity(const unsigned int new_id, const Entity& entity);
    Components CloneComponents() const;

protected:
    Entity(const unsigned int id = 0);

    // prohibit manual deletion
    virtual ~Entity() = default;
    void operator delete(void*) { }

    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        return AddBase<T>(this, std::forward<P>(p)...);
    }

public:
    const unsigned int id;

    template<typename T>
    T* const GetComponent() {
        return GetBase<T>();
    }
};

#endif//ENTITY_HPP_
