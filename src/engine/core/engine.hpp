#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <unordered_map>
#include <functional>
#include <exception>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>
#include <memory>
#include <list>

#include <engine/core/entity.hpp>
//class System;

typedef std::unique_ptr<Entity> Entity_ptr;
typedef std::list<Entity_ptr> Entity_list;

//typedef std::unique_ptr<System> System_ptr;

class Engine {
    private:
        unsigned int current_id = 0;
        std::unordered_map<std::type_index, Entity_list> entity_map;
        //std::vector<Entity_ptr> entities;
        //std::vector<System_ptr> systems;

        template<typename T>
        Entity_list& GetEntityList() {
            // search map for entity type
            auto map_it = entity_map.find(typeid(T));
            if (map_it == entity_map.end()) {
                // entity list does not exist
                throw new std::runtime_error("No existing entity of type: " + std::string(typeid(T).name()));
            }
            return map_it->second;
        }

    protected:

    public:
        template<typename T, class... P>
        T& AddEntity(P&&... p) {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");

            // get entity list specific to type. insert new one if non existent
            auto inserted_pair = entity_map.insert(std::pair<std::type_index, Entity_list>(typeid(T), Entity_list()));
            // insert returns pair with <iterator, found>
            Entity_list& entity_list = (*inserted_pair.first).second;

            // create new entity in list
            Entity_ptr& entity = entity_list.emplace_back(std::make_unique<T>(std::forward<P>(p)...));
            entity->id = current_id++;

            // cast to a reference
            return *(static_cast<T*>(entity.get()));
        }

        template<typename T>
        bool CheckEntity(const unsigned int index = 0) {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");

            // get entity list. return false if no entity of type T exists at all
            auto map_it = entity_map.find(typeid(T));
            if (map_it == entity_map.end()) {
                return false;
            }
            // check if index is exists in list
            Entity_list& Entity_list = map_it->second;
            if (index >= Entity_list.size()) {
                return false;
            }
            return true;
        }

        template<typename T>
        T& GetEntity(const unsigned int index = 0) {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");
            
            // get list of entity type
            Entity_list& entity_list = GetEntityList<T>();

            if (index >= entity_list.size()) {
                // entity index doesnt exist
                throw new std::runtime_error("Accessing non existing entity of type: " + std::string(typeid(T).name()));
            }
            auto list_it = entity_list.begin();
            std::advance(list_it, index);
            return *(static_cast<T*>((*list_it).get()));
        }

        template<typename T>
        std::vector<std::reference_wrapper<T>> GetEntities() {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");

            // get list of entity type
            Entity_list& entity_list = GetEntityList<T>();

            // create reference vector to entities
            std::vector<std::reference_wrapper<T>> ref_vec;
            ref_vec.reserve(entity_list.size());

            // fill vector with references from list and return
            for (auto it = entity_list.begin(); it != entity_list.end(); ++it) {
                 ref_vec.push_back(*(static_cast<T*>((*it).get())));
            }
            return ref_vec;
        }

        template<typename T>
        void DeleteEntity(T& entity) {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");

            // get list of entity type
            Entity_list& entity_list = GetEntityList<T>();

            for (auto it = entity_list.begin(); it != entity_list.end(); ++it) {
                 if (static_cast<T*>((*it).get()) != &entity) {
                     continue;
                 }
                 entity_list.erase(it);
                 return;
            }
            throw new std::runtime_error(
                "Deleting non existing entity of type: " + 
                std::string(typeid(T).name()) +
                ". Did you already delete it?"
            );
        }
};

#endif//ENGINE_HPP_
