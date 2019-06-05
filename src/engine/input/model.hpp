#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <vector>
#include <memory>
#include <iosfwd>
#include <engine/glm.hpp>

class fstream;

class Model {
public:
    Model() = default;
    static std::unique_ptr<Model> FromOBJ(std::istream& stream);

    std::vector<unsigned> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    // GLuint index_buffer_id;
    // GLuint vertex_buffer_id;
    // GLuint normal_buffer_id;
    // GLuint uv_buffer_id;
		
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

typedef std::unique_ptr<Model> Model_ptr;


#endif//MODEL_HPP_
