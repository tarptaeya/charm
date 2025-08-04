#include "charm.h"
#include <iostream>

class GameAdapter : public charm::AppAdapter {
    charm::Camera m_camera;
    charm::Renderer m_renderer;
    charm::Entity m_entity;
    charm::Texture2D m_texture;

public:
    GameAdapter()
    {
        glEnable(GL_DEPTH_TEST);

        charmShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        charmShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");
        charm::ShaderProgram program = std::move(charm::ShaderProgram(charmShaderRegistry->get_shader("assets/basic.vertex.glsl"), charmShaderRegistry->get_shader("assets/basic.fragment.glsl")));

        m_entity.add_component<charm::MeshRendererComponent>(charm::BoxGeometry(), charm::Material(std::move(program)));
        m_texture = charm::Texture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(charm::Matrix4f::perspective(M_PI_4, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_transform(charm::Matrix4f::identity() * charm::Matrix4f::translation(0, 0, 5));
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        static float theta = 0;
        theta += delta_time;
        charm::Matrix4f transform = charm::Matrix4f::identity();
        transform *= charm::Matrix4f::rotation_x(theta) * charm::Matrix4f::rotation_z(theta);
        m_entity.get_component<charm::TransformComponent>()->set_transform(transform);

        m_renderer.render(m_entity, m_camera);
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