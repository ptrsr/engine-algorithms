#include "entity.hpp"

Entity::Entity(const unsigned int id, const Entity& entity)
    : id(id)
    , components(entity.CloneComponents())
    { }

Entity::Entity(const unsigned int id)
    : id(id)
    { }

Components Entity::CloneComponents() const {
    Components copy;
    for (auto& pair : components) {
        Component* clone = pair.second->Clone();

        // move raw pointer into unique pointer
        Component_ptr clone_ptr;
        clone_ptr.reset(clone);

        // insert cloned component into cloned entity's components map
        copy.insert(std::make_pair<std::type_index, Component_ptr>(
                std::type_index(pair.first), std::move(clone_ptr)
            )
        );
    }
    return copy;
}
