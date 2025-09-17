#include "ch3db.h"
#include "io/BinaryIO.h"
#include <fstream>
#include <iostream>

namespace charm {

namespace ch3db {

    namespace {

        void read_meshes(std::ifstream& f, std::vector<Mesh>& meshes)
        {
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
        }

        std::shared_ptr<Skeleton> read_skeleton(std::ifstream& f)
        {
            unsigned int num_nodes = BinaryIO::read_unsigned_int(f);
            std::vector<std::shared_ptr<Skeleton>> nodes;
            std::unordered_map<int, std::shared_ptr<Skeleton>> bone_id_to_node;
            std::vector<int> parent_index(num_nodes + 1);
            for (int i = 0; i < num_nodes; ++i) {
                int bone_id = BinaryIO::read_int(f);
                int parent_id = BinaryIO::read_int(f);
                std::string name = BinaryIO::read_string(f);
                Mat4 transform = BinaryIO::read_mat4(f);

                auto node = std::make_shared<Skeleton>();
                node->bone_id = bone_id;
                node->name = name;
                node->transform = transform;
                nodes.push_back(node);

                bone_id_to_node[bone_id] = node;
                parent_index[bone_id] = parent_id;
            }

            int root_index = -1;
            for (const auto& node : nodes) {
                int bone_id = node->bone_id;
                int parent_id = parent_index[bone_id];
                if (parent_id == 0) {
                    root_index = bone_id;
                    std::cout << node->name << std::endl;
                } else {
                    auto& parent = bone_id_to_node[parent_id];
                    parent->children.push_back(node);
                }
            }

            if (root_index == -1) {
                std::cerr << "[error] ch3db: no root skeleton found" << std::endl;
                std::exit(0);
            }
            return nodes[root_index];
        }
    }

    Model Model::read(const std::string& path)
    {
        std::ifstream f(path, std::ios::binary);
        if (!f) {
            std::cerr << "[error] unable to open " << path << std::endl;
            std::exit(0);
        }

        std::vector<Mesh> meshes;
        read_meshes(f, meshes);

        Model model;
        model.meshes = meshes;
        model.root = read_skeleton(f);
        return model;
    }

}

}