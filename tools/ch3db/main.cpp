#include "charm.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace charm;

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
        }

        BinaryIO::write(f, (uint32_t)mesh.indices.size());
        for (const auto& index : mesh.indices) {
            BinaryIO::write(f, index);
        }
    }
}