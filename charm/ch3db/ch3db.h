#pragma once

#include "math/Mat4.h"
#include <string>
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
        std::vector<Skeleton*> children;

        Skeleton() = default;

        ~Skeleton();

        Skeleton(const Skeleton&) = delete;
        Skeleton& operator=(const Skeleton&) = delete;

        Skeleton(Skeleton&&);
        Skeleton& operator=(Skeleton&&);
    };

    struct Model {
        std::vector<Mesh> meshes;
        Skeleton* root = nullptr;

        Model() = default;

        ~Model();

        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;

        Model(Model&&);
        Model& operator=(Model&&);

        static Model read(const std::string&);
    };

}

}