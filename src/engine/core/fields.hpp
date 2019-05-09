#ifndef FIELD_HPP_
#define FIELD_HPP_

#include <unordered_map>
#include <any>
#include <string>

class Fields {
    protected:
        std::unordered_map<std::string, std::any> fields;

    public:
        template<typename T>
        T& AddField(std::string name, T initvalue = T()) {
            auto pair = fields.insert(std::pair<std::string, std::any>(name, initvalue));
            return std::any_cast<T&>(pair.first->second);
        }
};

#endif//FIELD_HPP_
