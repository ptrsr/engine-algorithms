#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>

class Component { 
    friend std::unique_ptr<Component>::deleter_type;

protected:
    virtual ~Component() = default;
};

#endif//COMPONENT_HPP_
