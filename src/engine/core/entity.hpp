#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>

#include <exception>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <memory>
#include <map>
#include <any>

typedef std::unordered_map<std::string, std::any> Fields;

class Entity {
    friend class Engine;

    public:
        template<typename T>
        T& GetComponent() {
            // assert if T is derived from component
            static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
            
            // find component and return reference
            auto map_it = components.find(typeid(T));
            if (map_it == components.end()) {
                throw new std::runtime_error("Accessing non existing component of type: " + std::string(typeid(T).name()));
            }
            // return reference
            Component* component = map_it->second.get();
            return *(static_cast<T*>(component));
        }

        template<typename T>
        bool CheckComponent() {
            static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
            auto map_it = components.find(typeid(T));
            return map_it != components.end();
        }

    protected:
        Entity() { };

        template<typename T, class... P>
        T& AddComponent(P&&... p) {
            // assert if T is derived from component
            static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
            
            // insert component. discards and returns previous if already exists
            auto pair = components.insert(std::pair<std::type_index, std::unique_ptr<Component>>(
                typeid(T),
                std::make_unique<T>(fields, std::forward<P>(p)...)
            ));
            
            // cast to reference
            Component* component = pair.first->second.get();
            return *(static_cast<T*>(component));
        }

    private:
        unsigned int id;
        std::map<std::type_index, std::unique_ptr<Component>> components;
        Fields fields;
};

#endif//ENTITY_HPP_
