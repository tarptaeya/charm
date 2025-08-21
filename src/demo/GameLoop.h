#pragma once

#include "charm.h"
#include "game_objects/RootObject.h"
#include "game_objects/TestObject.h"

using namespace charm;

class GameLoop : public IGameLoop {
    Camera m_camera;
    Renderer m_renderer;
    std::vector<Entity> m_entities;
    Texture2D m_texture;
    Texture2D m_bitmap;
    FontMetadata m_fontmetadata;
    RootObject m_root_object;
    Framebuffer m_main_framebuffer;
    Framebuffer m_hud_framebuffer;

public:
    GameLoop()
    {
        glEnable(GL_DEPTH_TEST);

        charmShaders.add("basic", Shader(FileIO::read_text("assets/basic.vertex.glsl"), FileIO::read_text("assets/basic.fragment.glsl")));
        charmShaders.add("ui", Shader(FileIO::read_text("assets/ui.vertex.glsl"), FileIO::read_text("assets/ui.fragment.glsl")));
        charmShaders.add("screen", Shader(FileIO::read_text("assets/screen.vertex.glsl"), FileIO::read_text("assets/screen.fragment.glsl")));
        charmShaders.add("font-test", Shader(FileIO::read_text("assets/font-test.vertex.glsl"), FileIO::read_text("assets/font-test.fragment.glsl")));
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

        // screen geometry
        {
            unsigned int vertex_array;
            glGenVertexArrays(1, &vertex_array);
            glBindVertexArray(vertex_array);

            unsigned int vertex_buffer;
            glGenBuffers(1, &vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
            // clang-format off
            float vertices[] = {
                -1, -1, 0, 0,
                -1, 1, 0, 1,
                1, 1, 1, 1,
                1, -1, 1, 0,
            };
            // clang-format on
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), 0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));

            unsigned int index_buffer;
            glGenBuffers(1, &index_buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
            // clang-format off
            unsigned int indices[] = {
                0, 2, 1,
                0, 3, 2,
            };
            // clang-format on
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            charmGeometries.add("screen-quad", Geometry(vertex_array, 6, { vertex_buffer, index_buffer }));
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
            m_root_object.add_object<TestObject>(transform);
        }

        m_texture = Texture2DBuilder("assets/DuckCM.png")
                        .set_texture_unit(GL_TEXTURE0)
                        .build();
        m_bitmap = Texture2DBuilder("assets/bitmap.png")
                       .set_texture_unit(GL_TEXTURE1)
                       .build();

        m_fontmetadata = FontMetadata::parse("assets/font.txt");

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

        m_main_framebuffer = FramebufferBuilder().create(1024, 720);
        m_hud_framebuffer = FramebufferBuilder().create(1024, 720);
    }

    ~GameLoop() override = default;

    void update(double delta_time) override
    {
        m_main_framebuffer.bind();
        update_main_framebuffer(delta_time);

        m_hud_framebuffer.bind();
        update_hud_framebuffer(delta_time);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, charmApp->get_width(), charmApp->get_height());
        update_screen_framebuffer(delta_time);
    }

    void update_main_framebuffer(double delta_time)
    {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        m_texture.bind();
        m_root_object.render(m_camera);
    }

    void update_hud_framebuffer(double delta_time)
    {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.78, 0.80, 0.82, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        m_bitmap.bind();
        charmShaders.get("ui").use();
        charmShaders.get("ui").set_uniform("u_font_texture", 1);
        charmShaders.get("ui").set_uniform("u_projection",
            Matrix4f({
                // clang-format off
                2 / 1024.0, 0,          0, 0,
                0,          -2 / 720.0, 0, 0,
                0,          0,          1, 0,
                -1,         1,          0, 1,
                // clang-format on
            }));
        imui::begin(22, 22, m_hud_framebuffer.get_width() / 3, m_hud_framebuffer.get_height() - 22 * 2, m_fontmetadata);
        imui::label("Hello, World!", 42);
        imui::label("This is message 1.", 42);
        imui::label("This is message 2!", 42);
        imui::label("Should this be messsage 1 + 2!?", 42);
        imui::end();

        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    }

    void update_screen_framebuffer(double delta_time)
    {
        glClearColor(0.3, 0.5, 0.7, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        charmShaders.get("screen").use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_hud_framebuffer.get_gl_color_texture());
        charmGeometries.get("screen-quad").draw();
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
