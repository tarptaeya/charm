#include "charm.h"
#include <iostream>

class CustomComponent : public charm::Component {
    charm::Geometry m_geometry;
    charm::Material m_material;

public:
    explicit CustomComponent(charm::Entity& entity, charm::Geometry&& geometry, charm::Material&& material)
        : Component(entity)
        , m_geometry(std::move(geometry))
        , m_material(std::move(material))
    {
    }

    ~CustomComponent() override = default;

    charm::Geometry& get_geometry()
    {
        return m_geometry;
    }

    charm::Material& get_material()
    {
        return m_material;
    }
};

class GameAdapter : public charm::AppAdapter {
    charm::Entity m_entity;
    charm::Texture2D m_texture_1;
    charm::Texture2D m_texture_2;

public:
    GameAdapter()
    {
        glEnable(GL_DEPTH_TEST);

        charmShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        charmShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");
        charm::ShaderProgram program = std::move(charm::ShaderProgram(charmShaderRegistry->get_shader("assets/basic.vertex.glsl"), charmShaderRegistry->get_shader("assets/basic.fragment.glsl")));

        charm::Geometry geometry = charm::BoxGeometry();
        charm::Material material(std::move(program));

        m_entity.add_component<CustomComponent>(std::move(geometry), std::move(material));
        m_texture_1 = charm::Texture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();
        m_texture_2 = charm::Texture2DBuilder("assets/awesomeface.ppm").set_texture_unit(GL_TEXTURE1).build();
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        static float theta = 0;
        theta += delta_time;

        auto component = m_entity.get_component<CustomComponent>();
        auto& geometry = component->get_geometry();
        auto& program = component->get_material().get_shader_program();

        program.use();

        m_texture_1.bind();
        program.set_uniform("u_texture_1", 0);

        m_texture_2.bind();
        program.set_uniform("u_texture_2", 1);

        charm::Matrix4f model = charm::Matrix4f::identity();
        model *= charm::Matrix4f::translation(0, 0, 0);
        program.set_uniform("u_model", model);

        static float x = 0;
        x = (x > 5) ? 0 : x + delta_time;
        charm::Matrix4f camera = charm::Matrix4f::identity();
        camera *= charm::Matrix4f::translation(x / 2, x / 2, 2 + x);
        camera.inverse();
        program.set_uniform("u_view", camera);

        charm::Matrix4f projection = charm::Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100.0);
        program.set_uniform("u_projection", projection);

        glBindVertexArray(geometry.get_vertex_array());
        glDrawElements(GL_TRIANGLES, geometry.get_count(), GL_UNSIGNED_INT, nullptr);
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