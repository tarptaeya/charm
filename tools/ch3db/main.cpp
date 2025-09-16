#include "charm.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace charm;

std::unordered_map<std::string, int> s_bone_to_id;

int get_bone_index(const std::string& name)
{
    if (!s_bone_to_id.count(name)) {
        static int id = 0;
        s_bone_to_id[name] = id++;
    }

    return s_bone_to_id[name];
}

ch3db::Mesh process_mesh(aiMesh* amesh, const aiScene* scene)
{
    std::vector<ch3db::Vertex> vertices;
    for (int i = 0; i < amesh->mNumVertices; ++i) {
        ch3db::Vertex vertex;
        vertex.position = { amesh->mVertices[i].x, amesh->mVertices[i].y, amesh->mVertices[i].z };
        vertex.normal = { amesh->mNormals[i].x, amesh->mNormals[i].y, amesh->mNormals[i].z };
        if (amesh->mTextureCoords[0]) {
            vertex.texcoord = { amesh->mTextureCoords[0][i].x, amesh->mTextureCoords[0][i].y };
        } else {
            vertex.texcoord = { 0, 0 };
        }

        vertices.push_back(vertex);
    }

    for (int i = 0; i < amesh->mNumBones; ++i) {
        auto abone = amesh->mBones[i];
        for (int j = 0; j < abone->mNumWeights; ++j) {
            auto vertex_weight = abone->mWeights[j];
            auto& vertex = vertices[vertex_weight.mVertexId];
            // Out of 4 bones for a vertex, find the first index whose weight is 0.
            // We can replace the bone at this index with the current bone as the
            // existing bone with weight 0 has no effect on animation.
            for (int k = 0; k < 4; ++k) {
                if (vertex.bone_weights[k] > 0) {
                    continue;
                }
                vertex.bone_ids[k] = get_bone_index(abone->mName.C_Str());
                vertex.bone_weights[k] = vertex_weight.mWeight;
                break;
            }
        }
    }

    std::vector<unsigned int> indices;
    for (int i = 0; i < amesh->mNumFaces; ++i) {
        aiFace face = amesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return { vertices, indices };
}

int main(int argc, const char** argv)
{
    if (argc != 3) {
        std::cout << "[usage] ch3db-conv <input-with-extension> <output-name>" << std::endl;
        std::exit(0);
    }

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(argv[1], aiProcess_Triangulate | aiProcess_LimitBoneWeights);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "[error] " << importer.GetErrorString() << std::endl;
        std::exit(0);
    }

    std::vector<ch3db::Mesh> meshes;
    for (int i = 0; i < scene->mNumMeshes; ++i) {
        meshes.push_back(process_mesh(scene->mMeshes[i], scene));
    }

    std::ofstream f(argv[2], std::ios::binary);
    if (!f) {
        std::cerr << "[error] cannot open " << argv[2] << std::endl;
        std::exit(0);
    }

    BinaryIO::write(f, (uint32_t)meshes.size());
    for (int i = 0; i < meshes.size(); ++i) {
        auto& mesh = meshes[i];

        BinaryIO::write(f, (uint32_t)mesh.vertices.size());
        for (const auto& vertex : mesh.vertices) {
            auto& position = vertex.position;
            BinaryIO::write(f, position.x);
            BinaryIO::write(f, position.y);
            BinaryIO::write(f, position.z);

            auto& normal = vertex.normal;
            BinaryIO::write(f, normal.x);
            BinaryIO::write(f, normal.y);
            BinaryIO::write(f, normal.z);

            auto& texcoord = vertex.texcoord;
            BinaryIO::write(f, texcoord.u);
            BinaryIO::write(f, texcoord.v);

            for (int j = 0; j < 4; ++j) {
                BinaryIO::write(f, vertex.bone_ids[j]);
                BinaryIO::write(f, vertex.bone_weights[j]);
            }
        }

        BinaryIO::write(f, (uint32_t)mesh.indices.size());
        for (const auto& index : mesh.indices) {
            BinaryIO::write(f, index);
        }
    }
}