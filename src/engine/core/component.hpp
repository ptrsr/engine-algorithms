#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <unordered_map>
#include <string>
#include <any>

typedef std::unordered_map<std::string, std::any> Fields;

class Component {
    protected:
        template<typename T>
        T& AddField(std::string name, T initvalue = T()) {
            auto pair = fields.insert(std::pair<std::string, std::any>(name, initvalue));
            return std::any_cast<T&>(pair.first->second);
        }

        Component(Fields& fields)
            : fields(fields) { };
    private:
        Fields& fields;
};

#endif//COMPONENT_HPP_
