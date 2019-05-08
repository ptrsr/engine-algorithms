#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <map>
#include <any>

enum Field {
    Transform
};

typedef std::map<Field, std::any> Fields;

#endif//FIELD_HPP_
