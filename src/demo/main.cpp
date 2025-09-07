#include "FPSCounter.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include <iostream>

using namespace charm;

class Example : public charm::IRootWidget {
    Camera m_camera;
    RootObject m_object;

    std::vector<ui::Label*> m_label_vec;
    ui::Checkbox* m_checkbox = nullptr;
    ui::Button* m_button1 = nullptr;
    ui::VBoxContainer* m_vbox = nullptr;
    ui::ScrollArea* m_scroll_area = nullptr;
    ui::ScrollArea* m_nested_scroll = nullptr;
    std::vector<ui::Button*> m_button_vec;
    ui::HBoxContainer* m_hbox = nullptr;
    ui::TextInput* m_input = nullptr;

    ui::Panel m_panel;

public:
    Example()
        : charm::IRootWidget()
    {
        glfwSwapInterval(0);

        {
            m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1.0, 0.1, 100));
            m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

            m_vbox = new ui::VBoxContainer;
            m_scroll_area = new ui::ScrollArea(m_vbox);

            m_input = new ui::TextInput;
            m_vbox->add(m_input);

            for (int i = 0; i < 10; ++i) {
                auto label = new ui::Label(std::to_string(i + 1) + ". Lorem Ipsum is simply dummy text of the printing and typesetting industry.");
                m_label_vec.push_back(label);
                m_vbox->add(label);
            }

            m_hbox = new ui::HBoxContainer;
            for (int i = 0; i < 5; ++i) {
                auto button = new ui::Button("Click Me");
                m_button_vec.push_back(button);
                m_hbox->add(button);
            }
            m_nested_scroll = new ui::ScrollArea(m_hbox);
            m_nested_scroll->set_is_width_expandable(false).set_is_height_expandable(false);
            m_vbox->add(m_nested_scroll);

            m_checkbox = new ui::Checkbox("I am a checkbox.");
            m_vbox->add(m_checkbox);

            m_button1 = new ui::Button("Click me");
            m_button1->set_on_click_handler([this] {
                for (const auto& label : m_label_vec) {
                    m_vbox->remove(label);
                }
            });
            m_vbox->add(m_button1);
        }

        {
            auto vbox = m_panel.create<ui::VBoxContainer>();
            auto scroll = m_panel.create<ui::ScrollArea>(vbox);
            m_panel.set_root(scroll);
        }
    }

    ~Example()
    {
        delete m_scroll_area;
        delete m_vbox;
        delete m_checkbox;
        delete m_button1;

        for (const auto& label : m_label_vec) {
            delete label;
        }

        delete m_nested_scroll;
        delete m_hbox;

        for (const auto& button : m_button_vec) {
            delete button;
        }

        delete m_input;
    }

    void update(double delta_time) override
    {
        gl::Context::reset_framebuffer(GL_FRAMEBUFFER);
        gl::Context::viewport(0, 0, charmApp.get_width(), charmApp.get_height());
        gl::Context::clear_color(0.3, 0.1, 0.2, 1.0);
        gl::Context::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object.render(m_camera);

        draw(m_scroll_area, 50, 50, 300, 150);

        m_panel.draw(50, 300, 300, 150);

        m_input->update(delta_time);
    }

    void on_char_callback(unsigned int codepoint) override
    {
        m_input->on_char_callback(codepoint);
    }

    void on_key_callback(int key, int scancode, int action, int mods) override
    {
        m_input->on_key_callback(key, scancode, action, mods);
    }

    void on_cursor_position_callback(double x, double y) override
    {
        m_scroll_area->on_cursor_pos_callback(x, y);
        m_checkbox->on_cursor_pos_callback(x, y);
        m_button1->on_cursor_pos_callback(x, y);
        m_nested_scroll->on_cursor_pos_callback(x, y);
        for (const auto& button : m_button_vec)
            button->on_cursor_pos_callback(x, y);
        m_input->on_cursor_pos_callback(x, y);
    }

    void on_mouse_button_callback(int button, int action, int mods) override
    {
        m_scroll_area->on_mouse_button_callback(button, action, mods);
        m_checkbox->on_mouse_button_callback(button, action, mods);
        m_button1->on_mouse_button_callback(button, action, mods);
        m_nested_scroll->on_mouse_button_callback(button, action, mods);
        for (const auto& b : m_button_vec)
            b->on_mouse_button_callback(button, action, mods);
        m_input->on_mouse_button_callback(button, action, mods);
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