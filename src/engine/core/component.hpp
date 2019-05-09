#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <engine/core/fields.hpp>

class Component {

    // protected:
    //     Component(Fields& fields);

    //     template<typename T>
    //     T& NewField(Fields field) {
    //         auto pair = fields.find(field);

    //         // if the field already exist, return ref to value
    //         if (pair != fields.end()) {
    //             return pair->second;
    //         }

    //         // return new field
    //         return fields.insert(std::pair<Field, std::any>(field, T())).second;
    //     }

    // private:
    //     Fields& fields;
};

#endif//COMPONENT_HPP_
