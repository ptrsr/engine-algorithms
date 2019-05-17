#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>

class Component { 
    friend class Entity;
    friend std::unique_ptr<Component>::deleter_type;

protected:
    // prohibit manual deletion
    virtual ~Component() = default;
    void operator delete(void*) { }
};

#endif//COMPONENT_HPP_
