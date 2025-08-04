#include "charm.h"
#include <iostream>

class GameAdapter : public XAppAdapter {
    XCamera m_camera;
    XRenderer m_renderer;
    std::vector<XEntity> m_entities;
    XTexture2D m_texture;
    XBoxGeometry m_box_geometry;

public:
    GameAdapter()
    {
        glEnable(GL_DEPTH_TEST);

        xShaders.add("basic.vertex", XShader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl"));
        xShaders.add("basic.fragment", XShader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl"));
        XProgram program = std::move(XProgram(xShaders.get("basic.vertex"), xShaders.get("basic.fragment")));
        xMaterials.add("basic", XMaterial(std::move(program)));

        for (int i = 0; i < 10; ++i) {
            XEntity entity;
            entity.add_component<XMeshRendererComponent>(m_box_geometry, xMaterials.get("basic"));
            m_entities.push_back(std::move(entity));
        }

        m_texture = XTexture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(XMatrix4f::perspective(M_PI_4, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_transform(XMatrix4f::identity() * XMatrix4f::translation(0, 0, 10));
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.2, 0.3, 1.0);

        static float theta = 0;
        theta += delta_time;

        int count = 0;
        for (XEntity& entity : m_entities) {
            ++count;
            XMatrix4f transform = XMatrix4f::identity();
            transform *= XMatrix4f::translation(count - 5, count - 3, -2 * count);
            theta *= -1;
            transform *= XMatrix4f::rotation_x(theta) * XMatrix4f::rotation_z(theta);
            entity.get_component<XTransformComponent>()->set_transform(transform);
            m_renderer.render(entity, m_camera);
        }
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