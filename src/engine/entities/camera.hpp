#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <engine/core/entity.hpp>
#include <engine/components/projector.hpp>
#include <engine/components/transform.hpp>

class Camera : public Entity {
public:
    Camera(const unsigned int id, const Projector::Context& context)
        : Entity(id)
        , transform(AddComponent<Transform>())
        , projector(AddComponent<Projector>(context))
        { }
    
    Transform& transform;
    Projector& projector;
};

#endif//CAMERA_HPP_
