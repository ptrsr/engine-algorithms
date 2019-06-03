#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>
#include <stdexcept>

template<class>
class TypeMap;

class Scene;
class Entity;

class Component {
    typedef std::unique_ptr<Component> Component_ptr;

    friend Entity;
    friend TypeMap<Component>;
    friend Component_ptr::deleter_type;

protected:
    // prohibit manual deletion
    void operator delete(void*) { }
    // proper deletion by Component pointer
    virtual ~Component() = default;

    Component(Entity* const entity = nullptr)
        : entity(entity)
        { }

    Component(Component& component)
        : entity(component.entity)
        { }

    virtual void Init(Scene& scene) { }
    
private:
    virtual Component* Clone() {
        throw new std::runtime_error("Clone function not implemented in derived class");
        return nullptr;
    };

public:
    Entity* const entity;
};

#endif//COMPONENT_HPP_
