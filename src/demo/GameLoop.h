#pragma once

#include "ScreenGeometry.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include "game_objects/TestObject.h"

using namespace charm;

class GameLoop : public AppAdapter {
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
        glViewport(0, 0, charmApp.get_width(), charmApp.get_height());
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
        glBindTexture(GL_TEXTURE_2D, m_main_framebuffer.get_gl_color_texture());
        ScreenGeometry::get_instance().get_geometry().draw();
    }
};
