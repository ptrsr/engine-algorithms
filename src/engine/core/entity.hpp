#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <typeindex>
#include <typeinfo>
#include <optional>
#include <utility>
#include <memory>
#include <map>
#include <any>

#include <engine/core/component.hpp>

typedef std::unique_ptr<Component> Component_ptr;

class Entity {
    friend class Engine;
    friend std::unique_ptr<Entity>::deleter_type;

private:
    unsigned int id;
    std::map<std::type_index, Component_ptr> components;

protected:
    virtual ~Entity() = default;
    Entity() = default;

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
            T* new_component = new T(std::forward<P>(p)...);
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
    template<typename T>
    std::optional<std::reference_wrapper<T>> GetComponent() {
        // assert if T is derived from component
        static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
        
        // find component and return reference
        auto map_it = components.find(typeid(T));
        if (map_it == components.end()) {
            // component does not exist, return empty optional
            return std::nullopt;
        }
        Component* component_ptr = map_it->second.get();
        T& component_ref = *(static_cast<T*>(component_ptr));
        // ref_wrapper and optional 
        return std::optional(std::ref(component_ref));
    }
};

#endif//ENTITY_HPP_
