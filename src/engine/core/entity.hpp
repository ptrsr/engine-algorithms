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

class Entity {
    friend class Engine;

private:
    unsigned int id;
    std::map<std::type_index, std::unique_ptr<Component>> components;

protected:
    Entity() { };

    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        // assert if T is derived from component
        static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
        
        // insert component. discards and returns previous if already exists
        auto pair = components.insert(std::make_pair<std::type_index, std::unique_ptr<T>>(
            typeid(T), std::make_unique<T>(std::forward<P>(p)...)
        ));
        
        // cast to reference
        Component* component_ptr = pair.first->second.get();
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
