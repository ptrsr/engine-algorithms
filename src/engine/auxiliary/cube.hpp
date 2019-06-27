#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <engine/glm.hpp>

#include <engine/core/component.hpp>
#include <engine/input/model.hpp>

class Cube : public Model {
public:
    Cube() {
        glm::vec3 ind[] = {
            // front vertices
            glm::vec3(-0.5f, -0.5f, -0.5f),	// 0
            glm::vec3( 0.5f, -0.5f, -0.5f),	// 1
            glm::vec3( 0.5f,  0.5f, -0.5f),	// 2
            glm::vec3(-0.5f,  0.5f, -0.5f),	// 3
            // rear vertices
            glm::vec3(-0.5f, -0.5f, 0.5f),	// 4
            glm::vec3( 0.5f, -0.5f, 0.5f),	// 5
            glm::vec3( 0.5f,  0.5f, 0.5f),	// 6
            glm::vec3(-0.5f,  0.5f, 0.5f)	// 7
        };
        vertices = {
            // front quad
            ind[0], ind[1],
            ind[1], ind[2],
            ind[2], ind[3],
            ind[3], ind[0],
            // rear quad
            ind[4], ind[5],
            ind[5], ind[6],
            ind[6], ind[7],
            ind[7], ind[4],
            // lines inbetween
            ind[0], ind[4],
            ind[1], ind[5],
            ind[2], ind[6],
            ind[3], ind[7]
        };
    }
};

#endif//CUBE_HPP_
