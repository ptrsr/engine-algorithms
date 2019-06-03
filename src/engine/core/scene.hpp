#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <unordered_map>
#include <exception>
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <memory>
#include <list>

#include <engine/auxiliary/check.hpp>
#include <engine/core/entity.hpp>

typedef std::shared_ptr<Entity> Entity_ptr;
typedef std::list<Entity_ptr> Entity_list;

class Scene {
private:
    unsigned int current_id = 0;
    std::unordered_map<std::type_index, Entity_list> entity_map;

    // get Entity_list of type T. return nullptr if non existant
    template<typename T>
    Entity_list* GetEntityList() {
        return GetEntityList(typeid(T));
    }

    // get Entity_list of type. return nullptr if non existant
    Entity_list* GetEntityList(std::type_index type) {
        // search map for entity type
        auto map_it = entity_map.find(type);
        if (map_it == entity_map.end()) {
            return nullptr;
        }
        /* NOTE: raw pointer because we're pointing to an element in an stl container,
                    only for internal usage */
        return &map_it->second;
    }

    // get Entity_list of type T. create new one if non existant
    template<typename T>
    Entity_list& ForceEntityList() {
        // if pair already exists, return reference. otherwise create new one and return reference
        auto inserted_pair = entity_map.insert(std::pair<std::type_index, Entity_list>(typeid(T), Entity_list()));
        // return ref to list
        return (*inserted_pair.first).second;
    }

    bool UnRegisterEntity(Entity& entity, std::type_index type, bool unRegisterInternal = true) {
        // get list of entity type
        Entity_list* entity_list = GetEntityList(type);

        // entity list doesn't even exist (entity has never been added to scene)
        if (!entity_list) {
            throw new std::runtime_error(
                "Deleting non existing entity of type: " + 
                std::string(type.name()) +
                ". Did you already delete it?"
            );
        }
        // find entity by iterating over list
        for (auto it = entity_list->begin(); it != entity_list->end(); ++it) {
            if ((*it).get() != &entity) {
                // continue searching if not found
                continue;
            }
            // remove entity
            entity_list->erase(it);

            if (unRegisterInternal) {
                // remove type from internal entity registery
                entity.UnRegister(type);
            }
            return true;
        }
        // entity wasn't found at all
        throw new std::runtime_error(
            "Deleting non existing entity of type: " + 
            std::string(type.name()) +
            ". Did you already delete it?"
        );
    }

public:
    template<typename T, class... P>
    T& AddEntity(P&&... p) {
        CheckType<Entity, T>();

        Entity_list& entity_list = ForceEntityList<T>();

        // manual creation of entity, store in smart pointer
        T* new_entity = new T(++current_id, std::forward<P>(p)...);
        Entity_ptr entity_ptr;
        entity_ptr.reset(static_cast<Entity*>(new_entity));

        // add type to entity for deletion later
        entity_ptr->Register<T>();
        
        // save shared pointer
        entity_list.push_back(std::move(entity_ptr));

        // allow entity to register or add new entities to scene on init
        new_entity->Init(*this);

        // return reference
        return *new_entity;
    }

    template<typename T, typename E>
    bool RegisterEntity(E& entity) {
        CheckType<Entity, T>();
        CheckType<T, E>();

        Entity_list* derived_entity_list = GetEntityList<E>();
    #ifdef DEBUG
        if (!derived_entity_list) {
            throw new std::runtime_error("List of type T does not exist.");
        }
    #endif
        for (auto it = derived_entity_list->rbegin(); it != derived_entity_list->rend(); ++it) {
            Entity_ptr entity_ptr = *it;
            if (&entity != entity_ptr.get()) {
                continue;
            }
            if (!entity_ptr->Register<T>()) {
                // entity already registered under type T
                return false;
            }
            // get list of new registery type
            Entity_list& base_entity_list = ForceEntityList<T>();

            base_entity_list.push_back(entity_ptr);
            return true;
        }

        // remove type from register since it hasn't properly been added
        entity.type_register.pop_back();
        throw new std::invalid_argument("Could not find original Entity_ptr.");
    }

    template<typename T>
    T* const GetEntity(const unsigned int index = 0) {
        CheckType<Entity, T>();
        
        // get list of entity type
        Entity_list* entity_list = GetEntityList<T>();

        if (!entity_list) {
            // no entities of type T exist at all
            return nullptr;
        }
        if (index >= entity_list->size()) {
            // index is outside of list
            return nullptr;
        }
        auto list_it = entity_list->begin();
        std::advance(list_it, index);

        // return a pointer (since return is not guaranteed)
        T* entity_ptr = static_cast<T*>((*list_it).get());
        return entity_ptr;
    }

    template<typename T>
    const std::vector<T*> GetEntities() {
        CheckType<Entity, T>();

        // get list of entity type
        Entity_list* entity_list = GetEntityList<T>();

        // create reference vector to entities
        std::vector<T*> ref_vec;

        if (!entity_list) {
            // return empty vec
            return ref_vec;
        }
        ref_vec.reserve(entity_list->size());

        // fill vector with references from list and return
        for (Entity_ptr& entity : *entity_list) {
            T* entity_ptr = static_cast<T*>(entity.get());
            ref_vec.push_back(entity_ptr);
        }
        return ref_vec;
    }

    template<typename T>
    T& CloneEntity(T& entity) {
        CheckType<Entity, T>();
        
        Entity* clone = new T(++current_id, entity);

        // convert to unique pointer
        Entity_ptr clone_ptr = Entity_ptr();
        clone_ptr.reset(clone);

        Entity_list* list = GetEntityList<T>();
    #ifdef DEBUG
        if (!list) {
            throw new std::runtime_error("List of type T does not exist.");
        }
    #endif
        list->push_back(std::move(clone_ptr));
        
        // return reference
        T& entity_ptr = *static_cast<T*>(clone);
        return entity_ptr;
    }

    template<typename T, typename E>
    bool UnRegisterEntity(E& entity) {
        CheckType<Entity, T>();
        CheckType<T, E>();

        return UnRegisterEntity(entity, typeid(T));
    }

    template<typename T>
    void DeleteEntity(T& entity) {
        CheckType<Entity, T>();

        Entity* base = static_cast<Entity*>(&entity);
        for (std::type_index type : base->type_register) {
            /* since entity is completely deleted, no need to
               keep track of the internal types */
            UnRegisterEntity(entity, type, false);
        }
    }
};

#endif//SCENE_HPP_
