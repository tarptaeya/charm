#pragma once

#include "math/Mat4.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace charm {

namespace ch3db {

    struct Position {
        float x;
        float y;
        float z;
    };

    struct Normal {
        float x;
        float y;
        float z;
    };

    struct Texcoord {
        float u;
        float v;
    };

    struct Vertex {
        Position position;
        Normal normal;
        Texcoord texcoord;
        int bone_ids[4] = { 0 };
        float bone_weights[4] = { 0 };
    };

    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    struct Skeleton {
        int bone_id = 0;
        std::string name;
        Mat4 transform;
        Mat4 inverse_bind_pose;
        std::vector<std::shared_ptr<Skeleton>> children;
    };

    struct Rotation {
        float w;
        float x;
        float y;
        float z;
    };

    struct Scale {
        float x;
        float y;
        float z;
    };

    struct Keyframe {
        float time;
        Position position;
        Rotation rotation;
        Scale scale;
    };

    struct Animation {
        std::string name;
        float duration;
        float ticks_per_second;
        std::unordered_map<std::string, std::vector<Keyframe>> keyframes;
    };

    struct Model {
        std::vector<Mesh> meshes;
        std::shared_ptr<Skeleton> root = nullptr;
        std::vector<Animation> animations;

        static Model read(const std::string&);
    };

}

}