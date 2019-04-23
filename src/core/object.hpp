#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>
#include <memory>
#include <iostream>

#include <glm.hpp>

class Object;
class World;

typedef std::shared_ptr<Object> Object_ptr;

class Object : public std::enable_shared_from_this<Object> {
    friend class World;
    public:
        // position
        const glm::mat4& GetTransform();
        glm::vec3 GetPosition();
        void SetPosition(const glm::vec3& position);

        void Translate(const glm::vec3& translation);

        void Rotate(const float angle, const glm::vec3& axis);

        bool AddChild(const Object_ptr& child);
        void UnParent();

        const Object_ptr GetParent() const;
        const std::vector<Object_ptr>& GetChildren() const;

        void Remove(const bool recursive = false);
        Object_ptr Clone(const bool recursive = false) const;

        void SendMessage(const Message& message);

        friend std::ostream& operator<< (std::ostream& os, const Object& object) {
            return os << object.transform;
        }

    protected:
        World& world;

    private:
        // private constructor
        Object(World& world);

        virtual Object* RawClone() const;

        // members
        Object_ptr parent;
        
        glm::mat4 transform;
        std::vector<Object_ptr> children;
};

#endif // OBJECT_HPP_
