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

/* a container class that holds data and functions
   to easily manipulate said data. it should not
   manipulate anything other than itself and it's
   contents.  */
class Component {
    friend Entity;
    friend TypeMap<Component>; // TODO: remove?

public:
    // parent entity owning this Component
    Entity* const entity;

    Component(Entity* const entity = nullptr)
        : entity(entity)
        { }

    // proper deletion by Component pointer
    virtual ~Component() = default;

protected:
    // helper function for Clone in derived class
    template<typename T, class... P> 
    Component_ptr Copy(P&&... p) {
        return Component_ptr(new T(std::forward<P>(p)...));
    }

private:
    // to be used when cloning an Entity (and it's Components!)
    virtual Component_ptr Clone(Entity* const entity) {
        throw new std::runtime_error("Clone function not implemented in derived class");
        return nullptr;
    };
};

/* a component of which only one exists and is shared between
   multiple Entities. this is useful for saving repetitive data
   that is similair between all derivatives of an Entity. */
class SharedComponent 
    : public Component
    , private std::enable_shared_from_this<SharedComponent> {
public:
    SharedComponent() = default;

    // provide a shared pointer of this
    virtual Component_ptr Clone(Entity* const entity) final override {
        return shared_from_this();
    }
    
private:
    /* there is no single owning entity. the owning Entities will
       neither be tracked. a derived type will exist as long as there
       is an Entity that has this */
    Entity* const entity;
};

#endif//COMPONENT_HPP_
