#include "hierarchical.hpp"

#include <stdexcept>

void Hierarchical::AddChild(Hierarchical& child) {
    if (child.parent != nullptr) {
        if (child.parent != this) {
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
    children.push_back(child);
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
        Hierarchical& child = (*i).get();
        if (&child != this) {
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

const std::vector<std::reference_wrapper<Hierarchical>>& Hierarchical::GetChildren() const {
    return children;
}
