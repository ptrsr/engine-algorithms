#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>
#include <engine/core/typemap.hpp>

#include <typeinfo>

class Scene;

class Entity : protected TypeMap<Component> {
    friend Scene;

public:
    const unsigned int id;

    Entity(const unsigned int id = 0)
        : id(id)
        { }

    template<typename T>
    T* const GetComponent() {
        return GetBase<T>();
    }

    // proper deletion by Entity pointer
    virtual ~Entity() = default;

protected:
    virtual void Init(Scene& scene) {
        for (auto& component_pair : *this) {
            component_pair.second->Init(scene);
        }
     }

    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        return AddBase<T>(this, std::forward<P>(p)...);
    }

    template<typename T>
    T& AddComponent(const std::shared_ptr<T>& shared_component) {
        T* const component = GetBase<T>();
        if (component) {
            throw new std::runtime_error("Cannot add component: already owns component type");
        }
    
        this->insert(std::make_pair<std::type_index, Component_ptr>(
                typeid(T), shared_component));

        return *shared_component;
    }

private:
    std::vector<std::type_index> type_register;

    // copy constructor
    Entity(const Entity& original, const unsigned int new_id)
        : id(new_id)
        , TypeMap<Component>(std::move(*original.Clone(this)))
        { }

    template<typename T>
    bool Register() {
        std::type_index new_info = typeid(T);

        for (std::type_index& info : type_register) {
            if (info == new_info) {
                return false;
            }
        }
        type_register.push_back(new_info);
        return true;
    }

    bool UnRegister(const std::type_index& type) {
        for (auto it = type_register.begin(); it != type_register.end(); ++it) {
            if ((*it) != type) {
                continue;
            }
            type_register.erase(it);
            return true;
        }
        return false;
    }
};

#endif//ENTITY_HPP_
