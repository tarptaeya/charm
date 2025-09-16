#include "Duck.h"

Duck::Duck()
{
    charm::ch3db::Model model = charm::ch3db::Model::read("res/demo/model.ch3db");
    for (const auto& mesh : model.meshes) {
        unsigned int vertex_array;
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        unsigned int vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(charm::ch3db::Vertex) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, position)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, normal)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, texcoord)));
        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 4, GL_INT, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, bone_ids)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(charm::ch3db::Vertex), (void*)(offsetof(charm::ch3db::Vertex, bone_weights)));

        unsigned int index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

        m_geometries.emplace_back(vertex_array, mesh.indices.size(), std::vector<unsigned int> { vertex_buffer, index_buffer });
    }
}

Duck::~Duck()
{
}

Duck::Duck(Duck&& other)
{
}

Duck& Duck::operator=(Duck&& other)
{
    if (this == &other)
        return *this;

    return *this;
}

std::vector<charm::Geometry>::const_iterator Duck::begin() const
{
    return m_geometries.begin();
}

std::vector<charm::Geometry>::const_iterator Duck::end() const
{
    return m_geometries.end();
}

Duck& Duck::get_instance()
{
    static Duck instance;
    return instance;
}