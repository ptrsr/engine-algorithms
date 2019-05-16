#ifndef HIERARCHICAL_HPP_
#define HIERARCHICAL_HPP_

#include <vector>
#include <functional>

#include <engine/core/component.hpp>

class Hierarchical : public Component {
    public:
        void AddChild(Hierarchical& child);
        void UnParent();

        Hierarchical* const GetParent() const;
        const std::vector<std::reference_wrapper<Hierarchical>>& GetChildren() const;

        //void Remove(const bool recursive = false);
        //Transform_ptr Clone(const bool recursive = false) const;

    private:
        // members
        Hierarchical* parent;
        std::vector<std::reference_wrapper<Hierarchical>> children;
};

#endif//HIERARCHICAL_HPP_
