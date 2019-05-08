#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <exception>

#include <engine/core/entity.hpp>
//class System;

typedef std::unique_ptr<Entity> Entity_ptr;
typedef std::list<Entity_ptr> Entity_list;

//typedef std::unique_ptr<System> System_ptr;

class Engine {
    public:
        template<typename T, class... U>
        T& AddEntity(U&&... u) {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");

            // get entity list specific to type. insert new one if non existent
            auto inserted_pair = entity_map.insert(std::pair<std::type_index, Entity_list>(typeid(T), Entity_list()));
            // insert returns pair with <iterator, found>
            Entity_list& entity_list = (*inserted_pair.first).second;

            // create new entity in list
            Entity_ptr& entity = entity_list.emplace_back(std::make_unique<T>(std::forward<U>(u)...));
            entity->id = current_id++;

            // cast to a reference
            return *(static_cast<T*>(entity.get()));
        }

        template<typename T>
        T& GetEntity(const unsigned int index = 0) {
            // assert if T is derived from entity
            static_assert(std::is_base_of<Entity, T>::value, "T must derived from entity");
            
            // search map for entity type
            auto map_it = entity_map.find(typeid(T));

            // entity list does not exist
            if (map_it == entity_map.end()) {
                throw new std::runtime_error("accessing non existing entity");
            }

            Entity_list& entity_list = map_it->second;
            // entity index doesnt exist
            if (index >= entity_list.size()) {
                throw new std::runtime_error("accessing non existing entity");
            }
            auto list_it = entity_list.begin();
            std::advance(list_it, index);
            return *(static_cast<T*>((*list_it).get()));
        }

    protected:
    private:
        unsigned int current_id = 0;

        std::unordered_map<std::type_index, Entity_list> entity_map;
        //std::vector<Entity_ptr> entities;
        //std::vector<System_ptr> systems;

};

#endif//ENGINE_HPP_
