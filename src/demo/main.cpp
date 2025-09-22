#include "UI.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include <iostream>

using namespace charm;

constexpr double window_width = 1024;
constexpr double window_height = 720;

void add_spacer(observer_ptr<ui::VBoxContainer>& container, ui::Panel* panel)
{
    container->add(panel->create<ui::Label>(" "));
}

class Example : public charm::AppAdapter {
    Camera m_camera;
    RootObject m_object;
    Skybox m_skybox;
    std::unique_ptr<UI> m_ui = nullptr;

public:
    Example()
        : charm::AppAdapter()
    {
        glfwSwapInterval(0);

        m_camera.set_projection(Mat4::perspective(M_PI / 3, window_width / window_height, 0.1, 100));
        m_camera.set_view(Mat4::look_at(Vec3(10, 3, 10), Vec3(5, 0, 5), Vec3(0, 1, 0)));

        m_skybox = Skybox({ "res/demo/skybox/right.jpg",
            "res/demo/skybox/left.jpg",
            "res/demo/skybox/top.jpg",
            "res/demo/skybox/bottom.jpg",
            "res/demo/skybox/front.jpg",
            "res/demo/skybox/back.jpg" });

        m_ui = std::make_unique<UI>();
    }

    ~Example()
    {
    }

    void update(double delta_time) override
    {
        gl::reset_framebuffer(GL_FRAMEBUFFER);
        gl::viewport(0, 0, charmApp.get_width(), charmApp.get_height());
        gl::clear_color(0.3, 0.1, 0.2, 1.0);
        gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object.update(delta_time);

        m_object.render(m_camera);
        m_skybox.render(m_camera);

        m_ui->update(delta_time);
        m_ui->draw(200, window_height - 250, window_width - 400, 200);
    }

    void on_char_callback(InputEventChar& event) override
    {
        m_ui->on_char_callback(event);
    }

    void on_key_callback(InputEventKey& event) override
    {
        m_ui->on_key_callback(event);
    }

    void on_cursor_position_callback(InputEventMouseMotion& event) override
    {
        m_ui->on_cursor_pos_callback(event);
    }

    void on_mouse_button_callback(InputEventMouseButton& event) override
    {
        m_ui->on_mouse_button_callback(event);
    }

    void on_scroll_callback(InputEventScroll& event) override
    {
        m_ui->on_scroll_callback(event);
    }
};

int main()
{
    AppOptions options;
    options.window_width = window_width;
    options.window_height = window_height;
    options.window_title = "Charmed Demo";
    options.font_texture_path = "res/charm/bitmap.png";
    options.font_metadata_path = "res/charm/font.txt";

    charmApp.initialize(options);

    Example example;
    return charmApp.exec(&example);
}