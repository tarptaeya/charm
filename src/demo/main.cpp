#include "charm.h"
#include <iostream>

using namespace charm;

class IGameObject {
public:
    virtual ~IGameObject() = default;
    virtual void update(double delta_time) { }
    virtual void render(Camera&) { }
};

class BoxObject : public IGameObject {
    Geometry& m_geometry;
    Material& m_material;
    Matrix4f m_transform;

public:
    BoxObject(const Matrix4f& transform)
        : m_geometry(charmGeometries.get("box"))
        , m_material(charmMaterials.get("basic"))
        , m_transform(transform)
    {
    }

    ~BoxObject() override { }

    void render(Camera& camera) override
    {
        m_material.use();
        m_material.set_uniform("u_model", m_transform);
        m_material.set_uniform("u_view", camera.get_view());
        m_material.set_uniform("u_projection", camera.get_projection());

        m_geometry.draw();
    }

    void set_transform(const Matrix4f& transform)
    {
        m_transform = transform;
    }
};

class RootObject : public IGameObject {
    std::vector<std::unique_ptr<IGameObject>> m_objects;

public:
    ~RootObject() = default;

    void render(Camera& camera) override
    {
        for (auto& object : m_objects) {
            object->render(camera);
        }
    }

    template <typename T, typename... Args>
    void add_object(Args&&... args)
    {
        auto object = std::make_unique<T>(std::forward<Args>(args)...);
        m_objects.push_back(std::move(object));
    }
};

class GameLoop : public IGameLoop {
    Camera m_camera;
    Renderer m_renderer;
    std::vector<Entity> m_entities;
    Texture2D m_texture;
    RootObject m_root_object;

public:
    GameLoop()
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
            Matrix4f transform = Matrix4f::identity();
            transform *= Matrix4f::translation(positions[i][0], positions[i][1], positions[i][2]);
            transform *= Matrix4f::rotation_x(i * 20) * Matrix4f::rotation_y(i * 10) * Matrix4f::rotation_z(i * 30);
            m_root_object.add_object<BoxObject>(transform);
        }

        m_texture = Texture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector4f(0, 0, 3), Vector4f(0, 0, 0), Vector4f(0, 1, 0)));
    }

    ~GameLoop() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.6, 0.7, 1.0);

        static Vector4f position(0, 0, 3);
        Vector4f front(0, 0, -1);

        float speed = 1.5 * delta_time;
        if (glfwGetKey(charmWindow, GLFW_KEY_W) == GLFW_PRESS) {
            position[2] -= speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        } else if (glfwGetKey(charmWindow, GLFW_KEY_S) == GLFW_PRESS) {
            position[2] += speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        } else if (glfwGetKey(charmWindow, GLFW_KEY_A) == GLFW_PRESS) {
            position[0] -= speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        } else if (glfwGetKey(charmWindow, GLFW_KEY_D) == GLFW_PRESS) {
            position[0] += speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector4f(0, 1, 0)));
        }

        m_root_object.update(delta_time);
        m_root_object.render(m_camera);
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

    Application::create<GameLoop>(options);
    return charmApp->exec();
}