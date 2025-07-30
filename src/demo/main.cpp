#include "charm.h"
#include <iostream>

class CustomVertexArrayComponent : public charm::Component {
    unsigned int m_vertex_array = 0;
    unsigned int m_vertex_buffer = 0;
    int m_count = 0;

public:
    explicit CustomVertexArrayComponent(charm::Entity& entity, unsigned int vertex_array, unsigned int vertex_buffer, int count)
        : m_vertex_array(vertex_array)
        , m_vertex_buffer(vertex_buffer)
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
        charmShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        charmShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");
        m_program = std::move(charm::ShaderProgram(charmShaderRegistry->get_shader("assets/basic.vertex.glsl"), charmShaderRegistry->get_shader("assets/basic.fragment.glsl")));

        unsigned int vertex_array;
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        unsigned int vertex_buffer;
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        float data[] = {
            -1,
            -1,
            0,
            1,
            1,
            0,
            1,
            1,
            0,
            1,
            1,
            -1,
            1,
            1,
            0,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 5 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)(2 * sizeof(float)));

        m_entity.add_component<CustomVertexArrayComponent>(vertex_array, vertex_buffer, 3);
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        m_program.use();
        charm::Matrix4f mat = charm::Matrix4f::identity();
        m_program.set_uniform("u_model", mat);

        auto component = m_entity.get_component<CustomVertexArrayComponent>();
        glBindVertexArray(component->get_vertex_array());
        glDrawArrays(GL_TRIANGLES, 0, component->get_count());
    }
};

int main()
{
    charm::AppOptions options;
    options.window_title = "Charmed Demo";

    charm::Application::create<GameAdapter>(options);
    return charmApp->exec();
}