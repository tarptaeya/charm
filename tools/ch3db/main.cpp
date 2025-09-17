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
std::unordered_map<std::string, aiMatrix4x4> s_bone_to_offset;

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

        s_bone_to_offset[abone->mName.C_Str()] = abone->mOffsetMatrix;
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
    skeleton->inverse_bind_pose = Mat4::identity();
    if (s_bone_to_offset.count(skeleton->name)) {
        auto offset = s_bone_to_offset[skeleton->name];
        skeleton->inverse_bind_pose = Mat4({
            // clang-format off
            {offset.a1, offset.a2, offset.a3, offset.a4},
            {offset.b1, offset.b2, offset.b3, offset.b4},
            {offset.c1, offset.c2, offset.c3, offset.c4},
            {offset.d1, offset.d2, offset.d3, offset.d4}
            // clang-format on
        });
    }
    for (int i = 0; i < anode->mNumChildren; ++i) {
        skeleton->children.push_back(process_skeleton(anode->mChildren[i], counter));
    }
    return skeleton;
}

ch3db::Animation process_animation(aiAnimation* scene_anim)
{
    ch3db::Animation animation;
    animation.name = scene_anim->mName.C_Str();
    animation.duration = scene_anim->mDuration;
    animation.ticks_per_second = scene_anim->mTicksPerSecond;
    for (int i = 0; i < scene_anim->mNumChannels; ++i) {
        auto* channel = scene_anim->mChannels[i];
        if (channel->mNumPositionKeys != channel->mNumRotationKeys || channel->mNumPositionKeys != channel->mNumScalingKeys) {
            std::cerr << "[error] position, rotation and scaling channel should have same number of keys" << std::endl;
            std::exit(0);
        }

        std::vector<ch3db::Keyframe> keyframes;
        for (int j = 0; j < channel->mNumPositionKeys; ++j) {
            auto position_key = channel->mPositionKeys[j];
            auto rotation_key = channel->mRotationKeys[j];
            auto scaling_key = channel->mScalingKeys[j];
            if (position_key.mTime != rotation_key.mTime || position_key.mTime != scaling_key.mTime) {
                std::cerr << "[error] all keys should be set at the same time" << std::endl;
                std::exit(0);
            }

            ch3db::Keyframe keyframe;
            keyframe.time = position_key.mTime;
            keyframe.position = ch3db::Position { position_key.mValue.x, position_key.mValue.y, position_key.mValue.z };
            keyframe.rotation = ch3db::Rotation { rotation_key.mValue.w, rotation_key.mValue.x, rotation_key.mValue.y, rotation_key.mValue.z };
            keyframe.scale = ch3db::Scale { scaling_key.mValue.x, scaling_key.mValue.y, scaling_key.mValue.z };
            keyframes.push_back(keyframe);
        }
        animation.keyframes[channel->mNodeName.C_Str()] = keyframes;
    }

    return animation;
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

    std::vector<ch3db::Animation> animations;
    for (int i = 0; i < scene->mNumAnimations; ++i) {
        animations.push_back(process_animation(scene->mAnimations[i]));
    }

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
        BinaryIO::write(f, curr->inverse_bind_pose);
    }

    // Write animation data to file
    BinaryIO::write(f, (uint32_t)animations.size());
    for (int i = 0; i < animations.size(); ++i) {
        BinaryIO::write(f, animations[i].name);
        BinaryIO::write(f, animations[i].duration);
        BinaryIO::write(f, animations[i].ticks_per_second);
        BinaryIO::write(f, (uint32_t)animations[i].keyframes.size());
        for (const auto& [k, vs] : animations[i].keyframes) {
            BinaryIO::write(f, k);
            BinaryIO::write(f, (uint32_t)vs.size());
            for (const auto& v : vs) {
                BinaryIO::write(f, v.time);
                BinaryIO::write(f, v.position.x);
                BinaryIO::write(f, v.position.y);
                BinaryIO::write(f, v.position.z);
                BinaryIO::write(f, v.rotation.w);
                BinaryIO::write(f, v.rotation.x);
                BinaryIO::write(f, v.rotation.y);
                BinaryIO::write(f, v.rotation.z);
                BinaryIO::write(f, v.scale.x);
                BinaryIO::write(f, v.scale.y);
                BinaryIO::write(f, v.scale.z);
            }
        }
    }
}