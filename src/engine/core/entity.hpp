#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <typeindex>
#include <typeinfo>
#include <utility>
#include <memory>
#include <map>
#include <any>

#include <engine/core/component.hpp>

typedef std::map<std::type_index, Component_ptr> Components;

class Entity {
    friend class Scene;
    friend std::unique_ptr<Entity>::deleter_type;

private:
    Components components;

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
        //  T should be derived from component
        static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
        
        Component* component_ptr;
        auto map_it = components.find(typeid(T));

        // when found
        if (map_it != components.end()) {
            component_ptr = map_it->second.get();
        } else {
            // create and insert new component
            T* new_component = new T(this, std::forward<P>(p)...);

            Component_ptr component_unique;
            component_unique.reset(static_cast<Component*>(new_component));

             // insert component. discards and returns previous if already exists
            auto pair = components.insert(
                std::make_pair<std::type_index, Component_ptr>(
                typeid(T), std::move(component_unique)));
        
            component_ptr = pair.first->second.get();
        }
        // cast to reference
        T& component_ref = *(static_cast<T*>(component_ptr));
        return component_ref;
    }

public:
    const unsigned int id;

    template<typename T>
    T* const GetComponent() {
        // assert if T is derived from component
        static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
        
        // find component and return reference
        auto map_it = components.find(typeid(T));
        if (map_it == components.end()) {
            // component does not exist, return empty optional
            return nullptr;
        }
        Component* component_ptr = map_it->second.get();
        return static_cast<T*>(component_ptr);
    }
};

#endif//ENTITY_HPP_
