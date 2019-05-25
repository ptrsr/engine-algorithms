#ifndef TYPECONTAINER_HPP_
#define TYPECONTAINER_HPP_

#include <typeindex>
#include <typeinfo>
#include <utility>
#include <memory>
#include <map>

template<typename B, typename T>
constexpr void CheckType() {
    static_assert(std::is_base_of<B, T>::value, "T must derived from base");
}

template<class Base>
class TypeContainer 
    : protected std::map<std::type_index, std::unique_ptr<Base>> {
    typedef std::unique_ptr<Base> Base_ptr;
    typedef std::map<std::type_index, Base_ptr> Base_map;

protected:
    // default constructor
    TypeContainer() = default;

    // copy constructor
    TypeContainer(Base_map container)
        : Base_map(std::move(container))
        { }

    template<typename T, class... P>
    T& AddBase(P&&... p) {
        CheckType<Base, T>();
        
        Base* base_ptr;
        auto map_it = this->find(typeid(T));

        // when found
        if (map_it != this->end()) {
            base_ptr = map_it->second.get();
        } else {
            // create and insert new component
            T* new_t = new T(std::forward<P>(p)...);

            Base_ptr base_u_ptr;
            base_u_ptr.reset(static_cast<Base*>(new_t));

             // insert component. discards and returns previous if already exists
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
};

#endif//TYPECONTAINER_HPP_
