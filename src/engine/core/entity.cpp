#include "entity.hpp"

Entity::Entity(const unsigned int id, const Entity& entity)
    : id(id)
    , TypeContainer(entity.CloneComponents())
    { }

Entity::Entity(const unsigned int id)
    : id(id)
    { }

Entity::Components Entity::CloneComponents() const {
    Entity::Components copy;
    for (auto& pair : *this) {
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
