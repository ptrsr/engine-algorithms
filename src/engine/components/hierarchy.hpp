#ifndef HIERARCHY_HPP_
#define HIERARCHY_HPP_

#include <vector>

#include <engine/core/component.hpp>

class Entity;

class Hierarchy : public Component {
private:
    // members
    Hierarchy* root = nullptr;
    Hierarchy* parent = nullptr;
    std::vector<Hierarchy*> children;

    void RemoveFromParent();

public:
    Hierarchy(Entity* const entity = nullptr, Hierarchy* const root = nullptr);

    // destructor
    ~Hierarchy();

    void AddChild(Hierarchy& child);
    void UnParent();

    Hierarchy* const GetParent() const;
    Hierarchy* const GetChild(const unsigned index = 0) const;
    const std::vector<Hierarchy*>& GetChildren() const;

    virtual Component_ptr Clone(Entity* const entity) override {
        return Copy<Hierarchy>(entity, root);
    }
    //void Remove(const bool recursive = false);
    //Transform_ptr Clone(const bool recursive = false) const;
};

#endif//HIERARCHY_HPP_
