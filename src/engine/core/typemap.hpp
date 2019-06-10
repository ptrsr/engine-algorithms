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
    : public std::map<std::type_index, std::shared_ptr<Base>> {
    typedef std::shared_ptr<Base> Base_ptr;
    typedef std::map<std::type_index, Base_ptr> Base_map;

public:
    TypeMap() = default;

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

    template<class... P>
    TypeMap* Clone(P&&... p) const {
        TypeMap* type_map = new TypeMap();

        for (auto& pair : *this) {
            Base_ptr clone = pair.second->Clone(std::forward<P>(p)...);

            // insert cloned bases into new typemap
            type_map->insert(std::make_pair<std::type_index, Base_ptr>(
                    std::type_index(pair.first), std::move(clone)
                )
            );
        }
        return type_map;
    }

protected:
    TypeMap(TypeMap&& original) noexcept 
    : std::map<std::type_index, std::shared_ptr<Base>>(original) 
    { }

private:
    TypeMap(const TypeMap& original) = default;

};

#endif//TYPEMAP_HPP_
