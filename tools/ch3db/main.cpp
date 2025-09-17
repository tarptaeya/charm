#include "charm.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace charm;

std::unordered_map<std::string, int> s_bone_to_id;

int get_bone_index(const std::string& name)
{
    if (!s_bone_to_id.count(name)) {
        // Bone id of 0 is reserved to represent the null node in the skeleton
        // This the bone ids start with 1 and 0 represents null bone.
        static int id = 0;
        s_bone_to_id[name] = ++id;
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

std::shared_ptr<ch3db::Skeleton> process_skeleton(aiNode* anode, uint32_t& counter)
{
    ++counter;
    auto skeleton = std::make_shared<ch3db::Skeleton>();
    skeleton->bone_id = get_bone_index(anode->mName.C_Str());
    skeleton->name = anode->mName.C_Str();
    skeleton->transform = Mat4({
        // clang-format off
        {anode->mTransformation.a1, anode->mTransformation.a2, anode->mTransformation.a3, anode->mTransformation.a4},
        {anode->mTransformation.b1, anode->mTransformation.b2, anode->mTransformation.b3, anode->mTransformation.b4},
        {anode->mTransformation.c1, anode->mTransformation.c2, anode->mTransformation.c3, anode->mTransformation.c4},
        {anode->mTransformation.d1, anode->mTransformation.d2, anode->mTransformation.d3, anode->mTransformation.d4}
        // clang-format on
    });
    for (int i = 0; i < anode->mNumChildren; ++i) {
        skeleton->children.push_back(process_skeleton(anode->mChildren[i], counter));
    }
    return skeleton;
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

    uint32_t num_skeleton_nodes = 0;
    auto skeleton_root_node = process_skeleton(scene->mRootNode, num_skeleton_nodes);

    std::ofstream f(argv[2], std::ios::binary);
    if (!f) {
        std::cerr << "[error] cannot open " << argv[2] << std::endl;
        std::exit(0);
    }

    // Write meshes to file
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

    // Write skeleton hierarchy to file
    BinaryIO::write(f, num_skeleton_nodes);
    std::stack<std::pair<ch3db::Skeleton*, ch3db::Skeleton*>> st;
    st.push({ skeleton_root_node.get(), nullptr });
    while (!st.empty()) {
        auto [curr, parent] = st.top();
        st.pop();
        for (const auto& child : curr->children) {
            st.push({ child.get(), curr });
        }

        BinaryIO::write(f, curr->bone_id);
        BinaryIO::write(f, parent ? parent->bone_id : 0);
        BinaryIO::write(f, curr->name);
        BinaryIO::write(f, curr->transform);
    }
}