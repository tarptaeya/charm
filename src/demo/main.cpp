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
    Material& m_material;
    Matrix4f m_transform;

public:
    BoxObject(const Matrix4f& transform)
        : m_material(charmMaterials.get("basic"))
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

        for (int i = 0; i < 1; ++i) {
            charmGeometries.get("model." + std::to_string(i)).draw();
        }
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
        charmGeometries.add("box", Geometry::box());

        {
            ch3db::Model model = ch3db::Model::read("assets/model.ch3db");
            int index = 0;
            for (const auto& mesh : model.meshes) {
                unsigned int vertex_array;
                glGenVertexArrays(1, &vertex_array);
                glBindVertexArray(vertex_array);

                unsigned int vertex_buffer;
                glGenBuffers(1, &vertex_buffer);
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), 0);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));

                unsigned int index_buffer;
                glGenBuffers(1, &index_buffer);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

                charmGeometries.add("model." + std::to_string(index++), Geometry(vertex_array, mesh.indices.size(), { vertex_buffer, index_buffer }));
            }
        }

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
            transform *= Matrix4f::scaling(0.0075);
            m_root_object.add_object<BoxObject>(transform);
        }

        m_texture = Texture2DBuilder("assets/container.ppm").set_texture_unit(GL_TEXTURE0).build();

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));
    }

    ~GameLoop() override = default;

    void update(double delta_time) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5, 0.6, 0.7, 1.0);

        static Vector3f position(0, 0, 3);
        Vector3f front(0, 0, -1);

        float speed = 1.5 * delta_time;
        if (glfwGetKey(charmWindow, GLFW_KEY_W) == GLFW_PRESS) {
            position[2] -= speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
        } else if (glfwGetKey(charmWindow, GLFW_KEY_S) == GLFW_PRESS) {
            position[2] += speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
        } else if (glfwGetKey(charmWindow, GLFW_KEY_A) == GLFW_PRESS) {
            position[0] -= speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
        } else if (glfwGetKey(charmWindow, GLFW_KEY_D) == GLFW_PRESS) {
            position[0] += speed;
            m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
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