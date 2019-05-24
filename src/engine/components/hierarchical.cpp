#include "hierarchical.hpp"

#include <stdexcept>
#include <iostream>

void Hierarchical::AddChild(Hierarchical& child) {
    if (child.parent != nullptr) {
        if (child.parent == this) {
            #ifdef DEBUG
            throw std::runtime_error("Cannot add child: already childed to this object.");
            #endif
            return;
        } else {
            // unparent if already attached
            child.UnParent();
        }
    }
    child.parent = this;
    children.push_back(&child);
}

void Hierarchical::UnParent() {
    if (parent == nullptr) {
        #ifdef DEBUG
        throw std::runtime_error("Cannot unparent: no parent.");
        #endif
        return;
    }
    // remove this from parent children list
    for (auto i = parent->children.begin(); i != parent->children.end(); ++i) {
        Hierarchical* child = *i;
        if (child != this) {
            continue;
        }
        parent->children.erase(i);
        break;
    }
    parent = nullptr;
}

Hierarchical* const Hierarchical::GetParent() const {
    return parent;
}

Hierarchical* const Hierarchical::GetChild(const unsigned int index) const {
    if (index >= children.size()) {
        return nullptr;
    }
    return children[index];
}

const std::vector<Hierarchical*>& Hierarchical::GetChildren() const {
    return children;
}

Hierarchical::~Hierarchical() {
    if (children.size() == 0 || !parent) {
        return;
    }
    Hierarchical* tmp_parent = parent;
    UnParent();

    // re-parent children to this parent 
    for (auto i = children.begin(); i != children.end(); ++i) {
        Hierarchical* child = *i;
        child->parent = tmp_parent;
        tmp_parent->children.push_back(child);
    }
}
