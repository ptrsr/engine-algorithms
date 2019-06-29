#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>
#include <engine/core/typemap.hpp>

#include <vector>
#include <typeinfo> // TODO: remove?

class Scene;

class Entity : private TypeMap<Component> {
    friend Scene;

public:
    // unique id
    const unsigned id;

    Entity(const unsigned id = 0)
        : id(id)
        { }

    // proper deletion by Entity pointer
    virtual ~Entity() = default;


    template<typename T>
    T* const GetComponent() {
        return GetBase<T>();
    }

    /* instantiate a Component of type T and foward a pointer 
       to this and the function parameters */
    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        T& component = AddBase<T>(this, std::forward<P>(p)...);
        component.entity = this;
        return component;
    }

    /* add a shared Component */
    template<typename T>
    T& AddComponent(std::shared_ptr<T> component) {
        CheckType<SharedComponent, T>();
        
        if (GetBase<T>()) {
            throw new std::runtime_error("Cannot add SharedComponent: already owns SharedComponent type");
        }

        this->insert(std::make_pair<std::type_index, Component_ptr>(
                typeid(T), component));

        return *component;
    }

    /* add a previously created Component */
    template<typename T>
    T& AddComponent(std::unique_ptr<T>&& component) {
        CheckType<Component, T>();
        
        if (GetBase<T>()) {
            throw new std::runtime_error("Cannot add Component: already owns Component type");
        }

        std::shared_ptr<T> component_ptr(std::move(component));
        component_ptr->entity = this;

        this->insert(std::make_pair<std::type_index, Component_ptr>(
                typeid(T), component_ptr));

        return *component_ptr.get();
    }

protected:
    // copy constructor
    Entity(const Entity& original, const unsigned new_id)
        : id(new_id)
        , TypeMap<Component>(std::move(*original.Clone(this)))
        { }

private:
    std::vector<std::type_index> type_register;

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
