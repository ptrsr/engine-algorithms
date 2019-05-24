#include "entity.hpp"

Entity::Entity(const Entity& entity, const unsigned int id)
    : id(id)
    , components(entity.CloneComponents())
    { }

Entity::Entity(const unsigned int new_id)
    : id(new_id)
    { }

Components Entity::CloneComponents() const {
    Components copy;
    for (auto it = components.begin(); it != components.end(); ++it) {
        Component* clone = (*it).second->Clone();

        // move raw pointer into unique pointer
        Component_ptr clone_ptr;
        clone_ptr.reset(clone);

        // insert cloned component into cloned entity's components map
        copy.insert(std::make_pair<std::type_index, Component_ptr>(
                std::type_index((*it).first), std::move(clone_ptr)
            )
        );
    }
    return copy;
}
