#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>
#include <memory>

class Object;
class Camera;
//class Light;

typedef std::shared_ptr<Object> Object_ptr;
//typedef std::shared_ptr<Light> Light_ptr;

class World {
    public:
        Object_ptr CreateObject();

        const std::vector<Object_ptr> GetChildren() const;

    private:
        std::vector<Object_ptr> children;
        //std::vector<Light_ptr> lights;

        std::shared_ptr<Camera> main_camera;

};

typedef std::shared_ptr<World> World_ptr;

#endif // WORLD_HPP_