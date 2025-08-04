#include "charm.h"
#include <iostream>

class GameAdapter : public XAppAdapter {
    XCamera m_camera;
    XRenderer m_renderer;
    XEntity m_entity;
    XTexture2D m_texture;

public:
    GameAdapter()
    {
        glEnable(GL_DEPTH_TEST);

        xShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        xShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");
        XProgram program = std::move(XProgram(xShaderRegistry->get_shader("assets/basic.vertex.glsl"), xShaderRegistry->get_shader("assets/basic.fragment.glsl")));

        m_entity.add_component<XMeshRendererComponent>(XBoxGeometry(), XMaterial(std::move(program)));
        m_texture = XTexture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(XMatrix4f::perspective(M_PI_4, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_transform(XMatrix4f::identity() * XMatrix4f::translation(0, 0, 5));
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        static float theta = 0;
        theta += delta_time;
        XMatrix4f transform = XMatrix4f::identity();
        transform *= XMatrix4f::rotation_x(theta) * XMatrix4f::rotation_z(theta);
        m_entity.get_component<XTransformComponent>()->set_transform(transform);

        m_renderer.render(m_entity, m_camera);
    }
};

int main()
{
    XAppOptions options;
    options.window_width = 1024;
    options.window_height = 720;
    options.window_title = "Charmed Demo";

    XApplication::create<GameAdapter>(options);
    return xApp->exec();
}