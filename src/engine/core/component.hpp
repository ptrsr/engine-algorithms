#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>

class Component;
typedef std::unique_ptr<Component> Component_ptr;

class Component { 
    friend class Entity;
    friend Component_ptr::deleter_type;

protected:
    // prohibit manual deletion
    virtual ~Component() = default;
    void operator delete(void*) { }

    virtual Component* Clone() = 0;
};

#endif//COMPONENT_HPP_
