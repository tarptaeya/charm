#include "FPSCounter.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include <iostream>

using namespace charm;

class Example : public charm::IRootWidget {
    Camera m_camera;
    RootObject m_object;

    ui::Panel m_panel;
    observer_ptr<ui::Label> m_fps_counter = nullptr;

public:
    Example()
        : charm::IRootWidget()
    {
        glfwSwapInterval(0);

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

        auto vbox = m_panel.create<ui::VBoxContainer>();
        auto scroll = m_panel.create<ui::ScrollArea>(vbox);

        auto main_container = m_panel.create<ui::VBoxContainer>();
        m_fps_counter = m_panel.create<ui::Label>("");
        main_container->add(m_fps_counter);
        main_container->add(scroll);
        m_panel.set_root(main_container);

        auto input = m_panel.create<ui::TextInput>();
        vbox->add(input);

        for (int i = 0; i < 10; ++i) {
            auto label = m_panel.create<ui::Label>(std::to_string(i + 1) + ". Lorem Ipsum is simply dummy text of the printing and typesetting industry.");
            vbox->add(label);
        }

        auto hbox = m_panel.create<ui::HBoxContainer>();
        for (int i = 0; i < 5; ++i) {
            auto button = m_panel.create<ui::Button>("Click Me");
            hbox->add(button);
        }

        auto nested_scroll = m_panel.create<ui::ScrollArea>(hbox);
        nested_scroll->set_is_width_expandable(false).set_is_height_expandable(false);
        vbox->add(nested_scroll);

        auto checkbox = m_panel.create<ui::Checkbox>("I am a checkbox!");
        vbox->add(checkbox);

        auto button = m_panel.create<ui::Button>("Remove labels");
        button->set_on_click_handler([] { });
        vbox->add(button);
    }

    ~Example()
    {
    }

    void update(double delta_time) override
    {
        gl::Context::reset_framebuffer(GL_FRAMEBUFFER);
        gl::Context::viewport(0, 0, charmApp.get_width(), charmApp.get_height());
        gl::Context::clear_color(0.3, 0.1, 0.2, 1.0);
        gl::Context::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object.render(m_camera);

        FPSCounter::get_instance().push(delta_time);
        m_fps_counter->set_text("FPS: " + std::to_string((int)FPSCounter::get_instance().get()));

        m_panel.update(delta_time);
        m_panel.draw(50, 300, 300, 150);
    }

    void on_char_callback(unsigned int codepoint) override
    {
        m_panel.on_char_callback(codepoint);
    }

    void on_key_callback(int key, int scancode, int action, int mods) override
    {
        m_panel.on_key_callback(key, scancode, action, mods);
    }

    void on_cursor_position_callback(double x, double y) override
    {
        m_panel.on_cursor_pos_callback(x, y);
    }

    void on_mouse_button_callback(int button, int action, int mods) override
    {
        m_panel.on_mouse_button_callback(button, action, mods);
    }
};

int main()
{
    AppOptions options;
    options.window_width = 800;
    options.window_height = 800;
    options.window_title = "Charmed Demo";
    options.font_texture_path = "res/charm/bitmap.png";
    options.font_metadata_path = "res/charm/font.txt";

    charmApp.initialize(options);

    Example example;
    return charmApp.exec(&example);
}