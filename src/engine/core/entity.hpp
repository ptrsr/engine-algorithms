#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/fields.hpp>
#include <engine/core/component.hpp>

#include <vector>
#include <memory>
#include <utility>
#include <map>
#include <any>

class Entity {
    friend class Engine;
    public:

    protected:
        Entity() { };

        template<typename T, class... P>
        T& AddComponent(P&&... p) {
            static_assert(std::is_base_of<Component, T>::value, "T must derived from component");
            std::unique_ptr<Component>& component = components.emplace_back(std::make_unique<T>(fields, std::forward<P>(p)...));
            return *(static_cast<T*>(component.get()));
        }

    private:
        unsigned int id;
        std::vector<std::unique_ptr<Component>> components;
        Fields fields;
};

#endif//ENTITY_HPP_
