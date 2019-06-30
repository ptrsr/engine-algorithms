#ifndef CUBE_COLLIDER_HPP_
#define CUBE_COLLIDER_HPP_

#include <engine/components/collider.hpp>


class CubeCollider : public Collider {
public:
    const float size;

    CubeCollider(const float size)
        : size(size)
        { }

    
};

#endif//CUBE_COLLIDER_HPP_
