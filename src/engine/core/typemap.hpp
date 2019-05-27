#ifndef TYPEMAP_HPP_
#define TYPEMAP_HPP_

#include <typeindex>
#include <typeinfo>
#include <utility>
#include <memory>
#include <map>

#include <engine/auxiliary/check.hpp>

template<class Base>
class TypeMap 
    : public std::map<std::type_index, std::unique_ptr<Base>> {
    typedef std::unique_ptr<Base> Base_ptr;
    typedef std::map<std::type_index, Base_ptr> Base_map;

public:
    template<typename T, class... P>
    T& AddBase(P&&... p) {
        CheckType<Base, T>();
        
        Base* base_ptr;
        auto map_it = this->find(typeid(T));

        // when found
        if (map_it != this->end()) {
            base_ptr = map_it->second.get();
        } else {
            // create new unique pointer to base
            T* new_t = new T(std::forward<P>(p)...);

            Base_ptr base_u_ptr;
            base_u_ptr.reset(static_cast<Base*>(new_t));

            // insert base
            auto pair = this->insert(
                std::make_pair<std::type_index, Base_ptr>(
                typeid(T), std::move(base_u_ptr)));
        
            base_ptr = pair.first->second.get();
        }
        // cast to reference
        T& base_ref = *static_cast<T*>(base_ptr);
        return base_ref;
    }

    template<typename T>
    T* const GetBase() {
        CheckType<Base, T>();

        // find component and return reference
        auto map_it = this->find(typeid(T));
        if (map_it == this->end()) {
            // component does not exist, return empty optional
            return nullptr;
        }
        Base* base_ptr = map_it->second.get();
        return static_cast<T*>(base_ptr);
    }

    // copy constructor
    TypeMap(const TypeMap& original) { 
        for (auto& pair : original) {
            Base* clone = pair.second->Clone();

            // move raw pointer into unique pointer
            Base_ptr clone_ptr;
            clone_ptr.reset(clone);

            // insert cloned bases into new typemap
            this->insert(std::make_pair<std::type_index, Base_ptr>(
                    std::type_index(pair.first), std::move(clone_ptr)
                )
            );
        }
    }

public:
    // default constructor
    TypeMap() = default;
};

#endif//TYPEMAP_HPP_
