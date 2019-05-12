#include "hierarchical.hpp"

#include <stdexcept>

void Hierarchical::AddChild(Hierarchical& child) {
    if (child.parent != nullptr) {
        if (child.parent == this) {
            throw std::runtime_error("Cannot add child: already childed to this object.");
        } else {
            // unparent if already attached
            child.UnParent();
        }
    }
    child.parent = this;
    children.push_back(child);
}

void Hierarchical::UnParent() {
    if (parent == nullptr) {
        throw std::runtime_error("Cannot unparent: no parent.");
    }
    for (auto i = parent->children.begin(); i != parent->children.end(); ++i) {
        if ((*i) != this) {
            continue;
        }
        parent->children.erase(i);
        break;
    }
    parent = nullptr;
}

const Hierarchical* Hierarchical::GetParent() const {
    return parent;
}

const std::vector<Hierarchical&>& Hierarchical::GetChildren() const {
    return children;
}
