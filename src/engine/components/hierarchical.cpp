#include "hierarchical.hpp"

#include <stdexcept>

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
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        Hierarchical* child = *it;
        if (child != this) {
            continue;
        }
        parent->children.erase(it);
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
    for (Hierarchical* child : children) {
        child->parent = tmp_parent;
        tmp_parent->children.push_back(child);
    }
}
