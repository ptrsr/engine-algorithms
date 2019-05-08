#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/field.hpp>
#include <engine/core/component.hpp>

#include <vector>
#include <memory>
#include <map>
#include <any>

typedef std::unique_ptr<Component> Component_ptr;

class Entity {
    friend class Engine;
    public:

    protected:
        Entity() { };

        template<typename T>
        std::unique_ptr<T>& AddComponent() {
            static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
            return components.emplace_back(std::make_unique<T>(fields));
        }

    private:
        unsigned int id;
        std::vector<Component_ptr> components;
        Fields fields;
};

#endif//ENTITY_HPP_
