#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <engine/core/entity.hpp>
#include <engine/components/projection.hpp>
#include <engine/components/transform.hpp>

class Camera : public Entity {
public:
    Camera(const unsigned int id, const ProjectionContext& context)
        : Entity(id)
        , transform(AddComponent<Transform>())
        , projection(AddComponent<Projection>(context))
        { }
    
    Transform& transform;
    Projection& projection;
};

#endif//CAMERA_HPP_
