#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>
#include <memory>

//#include <core/object.hpp>

class Object;
//class Camera;
//class Light;

typedef std::shared_ptr<Object> Object_ptr;
//typedef std::shared_ptr<Light> Light_ptr;

class World {
    public:
        Object_ptr CreateObject();
        const std::vector<Object_ptr> GetChildren() const;

    private:
        std::vector<Object_ptr> children;

};

typedef std::shared_ptr<World> World_ptr;

#endif // WORLD_HPP_