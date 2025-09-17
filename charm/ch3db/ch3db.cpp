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
                Mat4 inverse_bind_pose = BinaryIO::read_mat4(f);

                auto node = std::make_shared<Skeleton>();
                node->bone_id = bone_id;
                node->name = name;
                node->transform = transform;
                node->inverse_bind_pose = inverse_bind_pose;
                nodes.push_back(node);

                bone_id_to_node[bone_id] = node;
                parent_index[bone_id] = parent_id;
            }

            int root_index = -1;
            for (int i = 0; i < nodes.size(); ++i) {
                int bone_id = nodes[i]->bone_id;
                int parent_id = parent_index[bone_id];
                if (parent_id == 0) {
                    root_index = i;
                } else {
                    auto& parent = bone_id_to_node[parent_id];
                    parent->children.push_back(nodes[i]);
                }
            }

            if (root_index == -1) {
                std::cerr << "[error] ch3db: no root skeleton found" << std::endl;
                std::exit(0);
            }
            return nodes[root_index];
        }

        void read_animations(std::ifstream& f, std::vector<Animation>& animations)
        {
            int num_animations = BinaryIO::read_unsigned_int(f);
            for (int i = 0; i < num_animations; ++i) {
                Animation animation;
                animation.name = BinaryIO::read_string(f);
                animation.duration = BinaryIO::read_float(f);
                animation.ticks_per_second = BinaryIO::read_float(f);
                int num_keys = BinaryIO::read_unsigned_int(f);
                for (int j = 0; j < num_keys; ++j) {
                    std::string name = BinaryIO::read_string(f);
                    std::vector<Keyframe> keyframes;
                    int num_frames = BinaryIO::read_unsigned_int(f);
                    for (int k = 0; k < num_frames; ++k) {
                        Keyframe kf;
                        kf.time = BinaryIO::read_float(f);
                        kf.position.x = BinaryIO::read_float(f);
                        kf.position.y = BinaryIO::read_float(f);
                        kf.position.z = BinaryIO::read_float(f);
                        kf.rotation.w = BinaryIO::read_float(f);
                        kf.rotation.x = BinaryIO::read_float(f);
                        kf.rotation.y = BinaryIO::read_float(f);
                        kf.rotation.z = BinaryIO::read_float(f);
                        kf.scale.x = BinaryIO::read_float(f);
                        kf.scale.y = BinaryIO::read_float(f);
                        kf.scale.z = BinaryIO::read_float(f);
                        keyframes.push_back(kf);
                    }
                    animation.keyframes[name] = keyframes;
                }

                animations.push_back(animation);
            }
        }
    }

    Model Model::read(const std::string& path)
    {
        std::ifstream f(path, std::ios::binary);
        if (!f) {
            std::cerr << "[error] unable to open " << path << std::endl;
            std::exit(0);
        }
        Model model;
        read_meshes(f, model.meshes);
        model.root = read_skeleton(f);
        read_animations(f, model.animations);
        return model;
    }

}

}