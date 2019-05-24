#ifndef HIERARCHICAL_HPP_
#define HIERARCHICAL_HPP_

#include <vector>

#include <engine/core/component.hpp>

class Hierarchical : public Component {
private:
    // members
    Hierarchical* parent;
    std::vector<Hierarchical*> children;

public:
    virtual ~Hierarchical();

    using Component::Component;

    void AddChild(Hierarchical& child);
    void UnParent();

    Hierarchical* const GetParent() const;
    Hierarchical* const GetChild(const unsigned int index = 0) const;
    const std::vector<Hierarchical*>& GetChildren() const;

    virtual Component* Clone() override {
        return new Hierarchical(*this);
    }
    //void Remove(const bool recursive = false);
    //Transform_ptr Clone(const bool recursive = false) const;
};

#endif//HIERARCHICAL_HPP_
