#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>
#include <iostream>
class Component;
typedef std::unique_ptr<Component> Component_ptr;

class Entity;
class Component {
    friend class Entity;
    friend Component_ptr::deleter_type;

protected:
    // prohibit manual deletion
    virtual ~Component() = default;
    void operator delete(void*) { }

    Component(Entity* const entity = nullptr)
        : entity(entity)
        { }

    Component(Component& component)
        : entity(component.entity)
        { }

private:
    virtual Component* Clone() = 0;

public:
    Entity* const entity;
};

#endif//COMPONENT_HPP_
