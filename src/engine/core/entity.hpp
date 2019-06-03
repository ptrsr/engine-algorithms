#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <engine/core/component.hpp>
#include <engine/core/typemap.hpp>

#include <typeinfo>

class Scene;

class Entity : protected TypeMap<Component> {
    friend Scene;

private:

    // copy constructor
    Entity(const Entity& original, const unsigned int new_id)
        : id(new_id)
        , TypeMap<Component>(original)
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
        for (auto it = type_register.rbegin(); it != type_register.rend(); ++it) {
            if ((*it) != type) {
                continue;
            }
            type_register.erase(std::next(it).base());
            return true;
        }
        return false;
    }

protected:
    Entity(const unsigned int id = 0)
        : id(id)
        { }

    virtual void Init(Scene& scene) { }

    template<typename T, class... P>
    T& AddComponent(P&&... p) {
        return AddBase<T>(std::forward<P>(p)..., this);
    }

public:
    std::vector<std::type_index> type_register;

    // proper deletion by Entity pointer
    virtual ~Entity() = default;

    const unsigned int id;

    template<typename T>
    T* const GetComponent() {
        return GetBase<T>();
    }
};

#endif//ENTITY_HPP_
