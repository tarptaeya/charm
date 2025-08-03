#include "charm.h"
#include <iostream>

class CustomVertexArrayComponent : public charm::Component {
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    unsigned int m_index_buffer = 0;
    int m_count = 0;

public:
    explicit CustomVertexArrayComponent(charm::Entity& entity, unsigned int vertex_array, unsigned int vertex_buffer, unsigned int index_buffer, int count)
        : m_vertex_array(vertex_array)
        , m_vertex_buffer(vertex_buffer)
        , m_index_buffer(index_buffer)
        , m_count(count)
        , Component(entity)
    {
    }

    ~CustomVertexArrayComponent() override
    {
        if (m_vertex_array != 0)
            glDeleteVertexArrays(1, &m_vertex_array);
        if (m_vertex_buffer != 0)
            glDeleteBuffers(1, &m_vertex_buffer);
        if (m_index_buffer != 0)
            glDeleteBuffers(1, &m_index_buffer);
    }

    unsigned int get_vertex_array() const
    {
        return m_vertex_array;
    }

    int get_count() const
    {
        return m_count;
    }
};

class GameAdapter : public charm::AppAdapter {
    charm::ShaderProgram m_program;
    charm::Entity m_entity;

public:
    GameAdapter()
    {
        glEnable(GL_DEPTH_TEST);

        charmShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        charmShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");
        m_program = std::move(charm::ShaderProgram(charmShaderRegistry->get_shader("assets/basic.vertex.glsl"), charmShaderRegistry->get_shader("assets/basic.fragment.glsl")));

        unsigned int vertex_array;
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        unsigned int vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        // clang-format off
        float data[] = {
            -1, -1, 0, 1, 1, 0, 0,
            -1, 1, 1, 0, 1, 0, 1,
            1, 1, 1, 1, 1, 1, 1,
            1, -1, 1, 1, 0, 1, 0,
        };
        // clang-format on
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 7 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 7 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 7 * sizeof(float), (void*)(5 * sizeof(float)));

        unsigned int index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        // clang-format off
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
        };
        // clang-format on
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        m_entity.add_component<CustomVertexArrayComponent>(vertex_array, vertex_buffer, index_buffer, 6);

        auto image_data = charm::PPMReader::read("assets/texture.ppm");
        {
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_data.get_width(), image_data.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &image_data.get_data()[0]);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        static float theta = 0;
        theta += delta_time;

        m_program.use();

        charm::Matrix4f model = charm::Matrix4f::identity();
        model *= charm::Matrix4f::translation(0, 0, 0);
        m_program.set_uniform("u_model", model);

        static float x = 0;
        x = (x > 5) ? 0 : x + delta_time;
        charm::Matrix4f camera = charm::Matrix4f::identity();
        camera *= charm::Matrix4f::translation(0, 0, 2 + x);
        camera.inverse();
        m_program.set_uniform("u_view", camera);

        charm::Matrix4f projection = charm::Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100.0);
        m_program.set_uniform("u_projection", projection);

        auto component = m_entity.get_component<CustomVertexArrayComponent>();
        glBindVertexArray(component->get_vertex_array());
        glDrawElements(GL_TRIANGLES, component->get_count(), GL_UNSIGNED_INT, nullptr);
    }
};

int main()
{
    charm::AppOptions options;
    options.window_width = 1024;
    options.window_height = 720;
    options.window_title = "Charmed Demo";

    charm::Application::create<GameAdapter>(options);
    return charmApp->exec();
}