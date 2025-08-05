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
        xMaterials.add("basic", XMaterial(XProgram(xShaders.get("basic.vertex"), xShaders.get("basic.fragment"))));

        float positions[10][3] = {
            { 0, 0, 0 },
            { 2, 5, -15 },
            { -1.5, -2.2, -2.5 },
            { -3.8, -2.0, -12.3 },
            { 2.4, -0.4, -3.5 },
            { -1.7, 3.0, -7.5 },
            { 1.3, -2.0, -2.5 },
            { 1.5, 2.0, -2.5 },
            { 1.5, 0.2, -1.5 },
            { -1.3, 1.0, -1.5 }
        };

        for (int i = 0; i < 10; ++i) {
            XEntity entity;
            entity.add_component<XMeshRendererComponent>(m_box_geometry, xMaterials.get("basic"));
            XMatrix4f transform = XMatrix4f::identity();
            transform *= XMatrix4f::translation(positions[i][0], positions[i][1], positions[i][2]);
            transform *= XMatrix4f::rotation_x(i * 20) * XMatrix4f::rotation_y(i * 10) * XMatrix4f::rotation_z(i * 30);
            entity.get_component<XTransformComponent>()->set_transform(transform);
            m_entities.push_back(std::move(entity));
        }

        m_texture = XTexture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(XMatrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100));
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.6, 0.7, 1.0);

        static float theta = 0;
        theta += delta_time;
        float r = 5;
        m_camera.set_view(XMatrix4f::look_at(XVector4f(r * sin(theta), 0, r * cos(theta)), XVector4f(0, 0, 0), XVector4f(0, 1, 0)));

        for (XEntity& entity : m_entities) {
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