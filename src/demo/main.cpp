#include "charm.h"
#include <iostream>

using namespace charm;

class GameAdapter : public AppAdapter {
    Camera m_camera;
    Renderer m_renderer;
    std::vector<Entity> m_entities;
    Texture2D m_texture;

public:
    GameAdapter()
    {
        glEnable(GL_DEPTH_TEST);

        charmShaders.add("basic.vertex", Shader(GL_VERTEX_SHADER, FileIO::read_text("assets/basic.vertex.glsl")));
        charmShaders.add("basic.fragment", Shader(GL_FRAGMENT_SHADER, FileIO::read_text("assets/basic.fragment.glsl")));
        charmMaterials.add("basic", Material(Program(charmShaders.get("basic.vertex"), charmShaders.get("basic.fragment"))));
        charmGeometries.add("box", BoxGeometry());

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
            Entity entity;
            entity.add_component<MeshRendererComponent>(charmGeometries.get("box"), charmMaterials.get("basic"));
            Matrix4f transform = Matrix4f::identity();
            transform *= Matrix4f::translation(positions[i][0], positions[i][1], positions[i][2]);
            transform *= Matrix4f::rotation_x(i * 20) * Matrix4f::rotation_y(i * 10) * Matrix4f::rotation_z(i * 30);
            entity.get_component<TransformComponent>()->set_transform(transform);
            m_entities.push_back(std::move(entity));
        }

        m_texture = Texture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector4f(0, 0, 3), Vector4f(0, 0, 0), Vector4f(0, 1, 0)));
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.6, 0.7, 1.0);

        static Vector4f position(0, 0, 3);
        Vector4f front(0, 0, -1);

        float speed = 1.5 * delta_time;
        if (Input::is_key_pressed(GLFW_KEY_W)) {
            position[2] -= speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        } else if (Input::is_key_pressed(GLFW_KEY_S)) {
            position[2] += speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        } else if (Input::is_key_pressed(GLFW_KEY_A)) {
            position[0] -= speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        } else if (Input::is_key_pressed(GLFW_KEY_D)) {
            position[0] += speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        }

        for (Entity& entity : m_entities) {
            m_renderer.render(entity, m_camera);
        }
    }

    void on_key_input(int key, int scancode, int action, int mods) override
    {
    }

    void on_mouse_button(int button, int action, int mods) override
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            std::cout << "opening context menu..." << std::endl;
    }
};

int main()
{
    AppOptions options;
    options.window_width = 1024;
    options.window_height = 720;
    options.window_title = "Charmed Demo";

    Application::create<GameAdapter>(options);
    return charmApp->exec();
}