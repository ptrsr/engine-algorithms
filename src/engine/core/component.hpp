#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>
#include <stdexcept>

template<class>
class TypeMap;

class Scene;
class Entity;

class Component;
typedef std::shared_ptr<Component> Component_ptr;

class Component {
    friend Entity;
    friend TypeMap<Component>; // TODO: remove?

public:
    Entity* const entity;

    Component(Entity* const entity = nullptr)
        : entity(entity)
        { }

    // proper deletion by Component pointer
    virtual ~Component() = default;

protected:
    virtual void Init(Scene& scene) { }

    template<typename T, typename F> 
    Component_ptr Clone(T* original, F* forward = nullptr) {
        if (this != original) {
            throw std::runtime_error("Can only clone object where clone is called from");
        }
        return Component_ptr(new T(original, forward));
    }

private:
    virtual Component_ptr Clone(Entity* const entity) {
        throw new std::runtime_error("Clone function not implemented in derived class");
        return nullptr;
    };
};


class SharedComponent 
    : public Component
    , private std::enable_shared_from_this<SharedComponent> {
public:
    SharedComponent() = default;

    virtual Component_ptr Clone(Entity* const entity) final override {
        return shared_from_this();
    }
    
private:
    Entity* const entity;
};

#endif//COMPONENT_HPP_
