#include "model.hpp"

#include <istream>
#include <stdexcept>
#include <map>

bool StringCompare(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

Model_ptr Model::FromOBJ(std::istream& file) {
    Model_ptr model = std::make_unique<Model>();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    // triplets
    std::map<Triplet, unsigned int> triplets;
    // process by line
    std::string line;

    while (std::getline(file, line)) {
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
                &vertex_i[0], &vertex_i[1], &vertex_i[2],
                &normal_i[0], &normal_i[1], &normal_i[2],
                &uv_i[0],     &uv_i[1],     &uv_i[2]
            );

            if (read != 10) {
                throw new std::runtime_error("Could read model indices");
            }

            for (unsigned i = 0; i < 3; ++i) {
                Triplet triplet(vertex_i[i], normal_i[i], uv_i[i]);

                auto it = triplets.find(triplet);
                if (it == triplets.end()) {
                    // every index has uID
                    unsigned int index = triplets.size();
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
    return model;
}
