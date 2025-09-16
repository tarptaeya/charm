#include "ch3db.h"
#include "io/BinaryIO.h"
#include <fstream>
#include <iostream>

namespace charm {

namespace ch3db {

    Model Model::read(const std::string& path)
    {
        std::ifstream f(path, std::ios::binary);
        if (!f) {
            std::cerr << "[error] unable to open " << path << std::endl;
            std::exit(0);
        }

        std::vector<Mesh> meshes;

        int num_meshes = BinaryIO::read_unsigned_int(f);
        for (int i = 0; i < num_meshes; ++i) {
            int num_vertices = BinaryIO::read_unsigned_int(f);
            std::vector<Vertex> vertices;
            for (int j = 0; j < num_vertices; ++j) {
                Vertex vertex;

                vertex.position.x = BinaryIO::read_float(f);
                vertex.position.y = BinaryIO::read_float(f);
                vertex.position.z = BinaryIO::read_float(f);

                vertex.normal.x = BinaryIO::read_float(f);
                vertex.normal.y = BinaryIO::read_float(f);
                vertex.normal.z = BinaryIO::read_float(f);

                vertex.texcoord.u = BinaryIO::read_float(f);
                vertex.texcoord.v = BinaryIO::read_float(f);

                for (int i = 0; i < 4; ++i) {
                    vertex.bone_ids[i] = BinaryIO::read_int(f);
                    vertex.bone_weights[i] = BinaryIO::read_float(f);
                }

                vertices.push_back(vertex);
            }

            int num_indices = BinaryIO::read_unsigned_int(f);
            std::vector<unsigned int> indices;
            for (int j = 0; j < num_indices; ++j) {
                indices.push_back(BinaryIO::read_unsigned_int(f));
            }

            meshes.push_back({ vertices, indices });
        }

        return { meshes };
    }

}

}