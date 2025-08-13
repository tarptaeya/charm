#pragma once

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
    };

    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

    struct Model {
        std::vector<Mesh> meshes;

        static Model read(const std::string&);
    };

}

}