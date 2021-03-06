#include "model.hpp"

#include <engine/input/file.hpp>

#include <sstream>
#include <stdexcept>
#include <map>
#include <iostream>

bool StringCompare(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

Model_ptr Model::FromOBJ(const File& file) {
    return FromOBJ(file.content);
}

Model_ptr Model::FromOBJ(const std::string& data) {
    std::stringstream stream = std::stringstream(data, std::ios::in);

    Model_ptr model = std::make_shared<Model>();
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    // triplets
    std::map<Triplet, unsigned> triplets;
    // process by line
    std::string line;

    while (!stream.eof() && std::getline(stream, line)) {
        // read first two characters from each line
        char cmd[2];
        cmd[2] = 0;

        sscanf(line.c_str(), "%2s", cmd);

        if (StringCompare(cmd, "v")) {
            glm::vec3 vertex;
            sscanf(line.c_str(), "%2s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);

        } else if (StringCompare(cmd, "vn")) {
            glm::vec3 normal;
            sscanf(line.c_str(), "%2s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);

        } else if (StringCompare(cmd, "vt")) {
            glm::vec2 uv;
            sscanf(line.c_str(), "%2s %f %f ", cmd, &uv.x, &uv.y);
            uvs.push_back(uv);

        } else if (StringCompare(cmd, "f")) {
            // indices
            glm::ivec3 vertex_i;
            glm::ivec3 normal_i;
            glm::ivec3 uv_i;

            int read = sscanf(line.c_str(), "%2s %d/%d/%d %d/%d/%d %d/%d/%d", cmd,
                &vertex_i[0], &normal_i[0], &uv_i[0],
                &vertex_i[1], &normal_i[1], &uv_i[1],
                &vertex_i[2], &normal_i[2], &uv_i[2]
            );

            if (read != 10) {
                int count = sscanf(line.c_str(), "%2s %d %d %d", cmd, &vertex_i[0], &vertex_i[1], &vertex_i[2]);

                if (count == 4) {
                    glm::vec3 normal = glm::normalize(glm::cross(
                        vertices[vertex_i[1] - 1] - vertices[vertex_i[0] - 1], 
                        vertices[vertex_i[2] - 1] - vertices[vertex_i[0] - 1])
                    );

                    normals.push_back(normal);
                    normal_i = glm::ivec3(normals.size());

                    uvs.push_back(glm::vec2());
                    uv_i = glm::ivec3(uvs.size());
                } else {
                    std::cout << ".obj file not supported";
                    throw new std::runtime_error("Could not read model indices");
                }
            }

            for (unsigned i = 0; i < 3; ++i) {
                Triplet triplet(vertex_i[i], normal_i[i], uv_i[i]);

                auto it = triplets.find(triplet);
                if (it == triplets.end()) {
                    // every index has uID
                    unsigned index = triplets.size();
                    triplets[triplet] = index;

                    model->indices.push_back(index);
                    model->vertices.push_back(vertices[vertex_i[i] - 1]);
                    model->normals.push_back(normals[normal_i[i] - 1]);
                    model->uvs.push_back(uvs[uv_i[i] - 1]);
                } else {
                    model->indices.push_back(it->second);
                }
            }
        }
    }
    return std::move(model);
}
