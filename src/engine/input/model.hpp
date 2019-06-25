#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string>
#include <vector>
#include <memory>

#include <engine/glm.hpp>

class Model;
typedef std::shared_ptr<Model> Model_ptr; 

class File;

class Model {
public:
    Model() = default;

    static Model_ptr FromOBJ(const File& file);
    static Model_ptr FromOBJ(const std::string& data);

    std::vector<unsigned> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    struct Triplet {
        unsigned vert;
        unsigned norm;
        unsigned uv;
        
        Triplet(unsigned vert, unsigned norm, unsigned uv)
            : vert(vert)
            , norm(norm) 
            , uv(uv)
            { }
        
        // required for use as key in map
        bool operator < (const Triplet other) const {
            return memcmp((void*)this, (void*)&other, sizeof(Triplet)) > 0;
        }
    };
};

#endif//MODEL_HPP_
