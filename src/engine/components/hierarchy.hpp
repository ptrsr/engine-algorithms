#ifndef HIERARCHY_HPP_
#define HIERARCHY_HPP_

#include <vector>

#include <engine/core/component.hpp>

class Hierarchy : public Component {
private:
    // members
    Hierarchy* parent;
    std::vector<Hierarchy*> children;

public:
    // use component constructor
    using Component::Component;

    // destructor
    ~Hierarchy();

    void AddChild(Hierarchy& child);
    void UnParent();

    Hierarchy* const GetParent() const;
    Hierarchy* const GetChild(const unsigned int index = 0) const;
    const std::vector<Hierarchy*>& GetChildren() const;

    virtual Component* Clone() override {
        return new Hierarchy(*this);
    }
    //void Remove(const bool recursive = false);
    //Transform_ptr Clone(const bool recursive = false) const;
};

#endif//HIERARCHY_HPP_
