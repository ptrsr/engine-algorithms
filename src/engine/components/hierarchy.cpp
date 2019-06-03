#include "hierarchy.hpp"

#include <stdexcept>

#include <iostream>

Hierarchy::Hierarchy(Entity* const entity, Hierarchy* const root)
    : Component(entity)
    , root(root) {
    // add to root if given
    parent = root;
    if (root) {
        root->children.push_back(this);
    }
}

void Hierarchy::AddChild(Hierarchy& child) {
    if (child.parent != nullptr) {
        if (child.parent == this) {
        #ifdef DEBUG
            throw std::runtime_error("Cannot add child: already childed to this object.");
        #endif
            return;
        } else {
            // unparent if already attached
            child.RemoveFromParent();
        }
    }
    child.parent = this;
    children.push_back(&child);
}

void Hierarchy::RemoveFromParent() {
    if (!parent) {
        return;
    }
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        Hierarchy* child = *it;
        if (child != this) {
            continue;
        }
        parent->children.erase(it);
        break;
    }
}

void Hierarchy::UnParent() {
    // root can be either another hierarchical or a nullptr
    if (parent == root) {
        return;
    } 
    // remove this from parent children list
    RemoveFromParent();

    if (root) {
        root->children.push_back(this);
    }
    // either root or nullptr 
    parent = root;
}

Hierarchy* const Hierarchy::GetParent() const {
    return parent;
}

Hierarchy* const Hierarchy::GetChild(const unsigned int index) const {
    if (index >= children.size()) {
        return nullptr;
    }
    return children[index];
}

const std::vector<Hierarchy*>& Hierarchy::GetChildren() const {
    return children;
}

Hierarchy::~Hierarchy() {
    if (children.size() == 0 || !parent) {
        return;
    }
    Hierarchy* tmp_parent = parent;
    UnParent();

    // re-parent children to this parent 
    for (Hierarchy* child : children) {
        child->parent = tmp_parent;
        tmp_parent->children.push_back(child);
    }
}
