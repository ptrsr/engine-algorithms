#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <engine/entities/gameobject.hpp>
#include <engine/components/transform.hpp>
#include <engine/components/projection.hpp>

class Camera : public GameObject {
public:
    Camera(const unsigned int id, const ProjectionContext& context)
        : GameObject(id)
        , projection(AddComponent<Projection>(context))
        { }
    
    Projection& projection;
};

#endif//CAMERA_HPP_
