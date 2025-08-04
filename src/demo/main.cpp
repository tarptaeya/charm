#include "charm.h"
#include <iostream>

class GameAdapter : public charm::AppAdapter {
    charm::Renderer m_renderer;
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

        m_entity.add_component<charm::MeshRendererComponent>(std::move(geometry), std::move(material));
        m_texture_1 = charm::Texture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();
        m_texture_2 = charm::Texture2DBuilder("assets/awesomeface.ppm").set_texture_unit(GL_TEXTURE1).build();
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        m_renderer.render(m_entity);
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