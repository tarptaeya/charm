#include "OBJReader.h"
#include "charm_utils.h"
#include <fstream>
#include <iostream>
#include <math/Vector3f.h>
#include <sstream>

namespace charm {

Geometry OBJReader::read_geometry(const std::string& path)
{
    std::ifstream f(path);
    if (!f) {
        std::cerr << "[error] unable to read obj: " << path << std::endl;
        std::exit(1);
    }

    std::vector<Vector3f> positions;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    std::string line;
    while (std::getline(f, line)) {
        std::stringstream s(line);
        std::string tag;
        s >> tag;
        if (tag == "v") {
            float x, y, z;
            s >> x >> y >> z;
            positions.push_back(Vector3f(x, y, z));
        } else if (tag == "f") {
            std::vector<std::string> tokens = utils::split(line, ' ');
            for (int i = 3; i < tokens.size(); ++i) {
                std::string a = tokens[1];
                std::string b = tokens[i - 1];
                std::string c = tokens[i];

                for (const auto& x : { a, b, c }) {
                    auto y = utils::split(x, '/');
                    int ivertex = std::stoi(y[0]) - 1;
                    vertices.push_back(positions[ivertex].x());
                    vertices.push_back(positions[ivertex].y());
                    vertices.push_back(positions[ivertex].z());
                    indices.push_back(indices.size());
                }
            }
        }
    }

    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    unsigned int index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    return Geometry(vertex_array, indices.size(), std::vector<GLuint> { vertex_buffer, index_buffer });
}

}